#include "common/util/tesmappingstorage.h"
#include "common/util/tesoptions.h"
#include <unistd.h>
#include <cstring>

#define MAX_LINE_SIZE		5000

//-----------------------------------------------------------------------------
TESMappingStorage*	TESMappingStorage::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESMappingStorage::TESMappingStorage()
	:	_pCursor      (nullptr)
{}

//-----------------------------------------------------------------------------
TESMappingStorage::~TESMappingStorage()
{}

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
unsigned long  TESMappingStorage::tokenULong()
{
	char*			pColon(strchr(_pCursor, ','));
	unsigned long	value(0);

	if (pColon != nullptr) {
		*pColon = 0;
	}

	if (strchr(_pCursor, 'x') != NULL) {
		sscanf(_pCursor, "0x%X", &value);
	} else {
		value = atol(_pCursor);
	}
	
	if (pColon != nullptr) {
		*pColon = ',';
		_pCursor = pColon + 1;
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
					unsigned long	idTes5(tokenULong());
					string			master(tokenString());

					_mapTes3Tes5Ids[idTes3]._masterName = master;
					_mapTes3Tes5Ids[idTes3]._idTes5     = idTes5;
					break;
				}

				case TESMappingSection::TES5MATT: {
					break;
				}

				case TESMappingSection::TES5TXST: {
					break;
				}

				case TESMappingSection::TES5LTEX: {
					break;
				}

				case TESMappingSection::DEFAULTS: {
					string		token(tokenString());

					if (token == "TES3TES5") {
						_defaultTes5Id._idTes5     = tokenULong();
						_defaultTes5Id._masterName = tokenString();
					}


					break;
				}
			}  //  switch (section)
		}  //  while (true)

		fclose(pFile);
		retCode = true;


		verbose2("DEFAULTS - TES3TES5:: 0x%08X [%s]\n", _defaultTes5Id._idTes5, _defaultTes5Id._masterName.c_str());
		for (auto& entry : _mapTes3Tes5Ids) {
			verbose2("TES3TES5:: 0x%08X -> 0x%08X [%s]", entry.first, entry.second._idTes5, entry.second._masterName.c_str());
		}
		verbose2("");

	}  //  if (pFile != NULL)

	return retCode;
}

//-----------------------------------------------------------------------------
TESMapTes3Ids& TESMappingStorage::mapTes3Id(unsigned long const tes3Id)
{
	if (_mapTes3Tes5Ids.count(tes3Id) > 0)		return _mapTes3Tes5Ids[tes3Id];

	return _defaultTes5Id;
}