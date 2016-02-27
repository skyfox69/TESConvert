#include "common/util/tesmappingstorage.h"
#include "common/util/tesoptions.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/subrecord/tes4subrecordsinglestring.h"
#include "tes4/subrecord/tes4subrecordsingleushort.h"
#include "tes4/subrecord/tes4subrecordobnd.h"
#include <unistd.h>
#include <cstring>
#include <algorithm>

#define MAX_LINE_SIZE		5000

//-----------------------------------------------------------------------------
TESMappingStorage*	TESMappingStorage::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESMappingStorage::TESMappingStorage()
	:	_pCursor (nullptr),
		_pseudoId(0x7000000) 
{}

//-----------------------------------------------------------------------------
TESMappingStorage::~TESMappingStorage()
{
	for_each(_mapTes5Txst.begin(), _mapTes5Txst.end(), [](auto item) -> void {
		delete item.second;
	});
}

//-----------------------------------------------------------------------------
TESMappingStorage* TESMappingStorage::getInstance()
{
	if (_pInstance == nullptr) {
		_pInstance = new TESMappingStorage();
	}
	
	return _pInstance;
}

//-----------------------------------------------------------------------------
string TESMappingStorage::tokenString()
{
	char*	pColon(strchr(_pCursor, ','));
	string	text;

	if (pColon == nullptr) {
		pColon = strchr(_pCursor, '#');
	}
	if (pColon == nullptr) {
		pColon = strchr(_pCursor, '\n');
	}

	if (pColon != nullptr) {
		*pColon = 0;
	}

	text = _pCursor;

	if (pColon != nullptr) {
		*pColon = ',';
		_pCursor = pColon + 1;
	}

	return text.erase(text.find_last_not_of(" \n\r\t")+1);
}

//-----------------------------------------------------------------------------
unsigned long TESMappingStorage::tokenULong()
{
	string			token(tokenString());
	unsigned long	value(0);

	if (strchr(token.c_str(), 'x') != NULL) {
		sscanf(token.c_str(), "0x%X", &value);
	} else {
		value = atol(token.c_str());
	}

	return value;
}

//-----------------------------------------------------------------------------
unsigned short TESMappingStorage::tokenUShort()
{
	string			token(tokenString());
	unsigned long	value(0);

	if (strchr(token.c_str(), 'x') != NULL) {
		sscanf(token.c_str(), "0x%X", &value);
	} else {
		value = atoi(token.c_str());
	}

	return (short) value;
}

//-----------------------------------------------------------------------------
unsigned long TESMappingStorage::tokenFormId()
{
	char*			pCursorSave(_pCursor);
	string			tokenKey   (tokenString());
	unsigned long	value      (0);

	if (tokenKey[0] != '$') {
		_pCursor = pCursorSave;
		value = tokenULong();
	} else if (_mapPseudoIds.count(tokenKey) > 0) {
		value = _mapPseudoIds[tokenKey];
	} else {
		value = _pseudoId++;
		_mapPseudoIds[tokenKey] = value;
	}

	return value;
}

//-----------------------------------------------------------------------------
bool TESMappingStorage::initialize()
{
	FILE*	pFile  (fopen(TESOptions::getInstance()->_fileNameM.c_str(), "rb"));
	bool	retCode(false);

	if (pFile != NULL) {
		char	cBuffer[MAX_LINE_SIZE] = {0};
		TESMappingStorage::TESMappingSection	section(TESMappingSection::UNKNOWN);

		verbose0("initializing from textures.map");
		while (true) {
			_pCursor = fgets(cBuffer, MAX_LINE_SIZE, pFile);

			if (_pCursor == nullptr)			break;
			if (_pCursor[0] == 0)				continue;
			if (_pCursor[0] == 0x1a)			continue;
			if (_pCursor[0] == 0x0a)			continue;
			if (_pCursor[0] == '#')				continue;		//  pure comment row

			//  start of new section
			if (_pCursor[0] == '[') {
				if (strncmp(_pCursor, "[TES3TES5]", 10) == 0)		section = TESMappingSection::TES3TES5;
				if (strncmp(_pCursor, "[TES5MATT]", 10) == 0)		section = TESMappingSection::TES5MATT;
				if (strncmp(_pCursor, "[TES5TXST]", 10) == 0)		section = TESMappingSection::TES5TXST;
				if (strncmp(_pCursor, "[TES5LTEX]", 10) == 0)		section = TESMappingSection::TES5LTEX;
				if (strncmp(_pCursor, "[DEFAULTS]", 10) == 0)		section = TESMappingSection::DEFAULTS;
				continue;
			}

			//  decode entry
			switch (section) {
				case TESMappingSection::TES3TES5: {
					unsigned long	idTes3(tokenULong());
					unsigned long	idTes5(tokenFormId());
					string			master(tokenString());

					_mapTes3Tes5Ids[idTes3]._masterName = master;
					_mapTes3Tes5Ids[idTes3]._idTes5     = idTes5;
					break;
				}

				case TESMappingSection::TES5MATT: {
					break;
				}

				case TESMappingSection::TES5TXST: {
					createTXST();
					break;
				}

				case TESMappingSection::TES5LTEX: {
					break;
				}

				case TESMappingSection::DEFAULTS: {
					string		token(tokenString());

					if (token == "TES3TES5") {
						_defaultTes5Id._idTes5     = tokenFormId();
						_defaultTes5Id._masterName = tokenString();
					}


					break;
				}
			}  //  switch (section)
		}  //  while (true)

		fclose(pFile);
		retCode = true;
		verbose0("done");


		verbose2("DEFAULTS - TES3TES5:: 0x%08X [%s]\n", _defaultTes5Id._idTes5, _defaultTes5Id._masterName.c_str());
		for (auto& entry : _mapTes3Tes5Ids) {
			verbose2("TES3TES5:: 0x%08X -> 0x%08X [%s]", entry.first, entry.second._idTes5, entry.second._masterName.c_str());
		}
		verbose2("");
		for (auto& entry : _mapPseudoIds) {
			verbose2("PseudoId:: %s -> 0x%08X", entry.first.c_str(), entry.second);
		}
		verbose2("");
		for (auto& entry : _mapTes5Txst) {
			Tes4SubRecordSingleString*	pString((Tes4SubRecordSingleString* )entry.second->findSubRecord("EDID"));

			verbose2("TES5TXST:: 0x%08X -> %s", entry.first, ((pString != nullptr) ? pString->_text.c_str() : ""));
		}
		verbose2("");

	}  //  if (pFile != NULL)

	exit(0);
	
	return retCode;
}

//-----------------------------------------------------------------------------
TESMapTes3Ids& TESMappingStorage::mapTes3Id(unsigned long const tes3Id)
{
	return ((_mapTes3Tes5Ids.count(tes3Id) > 0) ? _mapTes3Tes5Ids[tes3Id] :_defaultTes5Id);
}

//-----------------------------------------------------------------------------
void TESMappingStorage::createTXST()
{
	Tes4RecordGeneric*	pTXST(new Tes4RecordGeneric("TXST", tokenFormId()));
	string				tmpStr;

	//  EDID
	tmpStr = tokenString();
	if (!tmpStr.empty()) {
		pTXST->push_back(new Tes4SubRecordSingleString("EDID", tmpStr));
	}

	//  OBND
	pTXST->push_back(new Tes4SubRecordOBND());

	//  TX00
	tmpStr = tokenString();
	if (!tmpStr.empty()) {
		pTXST->push_back(new Tes4SubRecordSingleString("TX00", tmpStr));
	}

	//  TX01
	tmpStr = tokenString();
	if (!tmpStr.empty()) {
		pTXST->push_back(new Tes4SubRecordSingleString("TX01", tmpStr));
	}

	// DNAM
	char*	pCursorSave(_pCursor);

	tmpStr = tokenString();
	if (!tmpStr.empty()) {
		_pCursor = pCursorSave;
		pTXST->push_back(new Tes4SubRecordSingleUShort("DNAM", tokenUShort()));
	}

	//  add new element
	_mapTes5Txst[pTXST->_id] = pTXST;
}