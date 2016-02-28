#include "common/tesprocessor.h"
#include "common/itesprocessor.h"
#include "common/util/tesoptions.h"
#include "common/util/bitmap.h"
#include "record/tesrecordbase.h"
#include "tes3/tes3processor.h"
#include "tes4/tes4processor.h"
#include "tes4/tes4converter.h"
#include "record/tesrecordmain.h"
#include "record/tesrecordgroup.h"
#include <cstring>

//-----------------------------------------------------------------------------
TesProcessor*	TesProcessor::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TesProcessor::TesProcessor()
{}

//-----------------------------------------------------------------------------
TesProcessor::~TesProcessor()
{}

//-----------------------------------------------------------------------------
TesProcessor* TesProcessor::getInstance()
{
	if (_pInstance == nullptr) {
		_pInstance = new TesProcessor();
	}
	
	return _pInstance;
}

//-----------------------------------------------------------------------------
bool TesProcessor::process(int argc, char** argv, int offset)
{
	TESOptions*		pOptions(TESOptions::getInstance());
	bool			isParsed(true);
	
	for (int i(offset); (i < argc) && isParsed; ++i) {
		isParsed &= parse(argv[i]);
	}
	
	if (isParsed) {
		ITesProcessor*	pSubProcessor(nullptr);

		switch (_parser.fileType()) {
			case TesFileType::TES3:
				pSubProcessor = new Tes3Processor(_mapRecords);
				break;
			case TesFileType::TES4:
				pSubProcessor = new Tes4Processor(_mapRecords, _parser);
				break;
		}

		//  dump token structure by token name
		if (pOptions->_dumpFinalT) {
			dumpTokensByName(pOptions->_expToken);
		}
		//  dump token structure by file appearance
		if (pOptions->_dumpFinalS) {
			dumpTokensBySequence();
		}
		//  dump token structure by file appearance as XML
		if (pOptions->_dumpFinalX) {
			dumpTokensBySequenceAsXml();
		}
		//  dump all used tokens
		if (pOptions->_dumpUsedTags) {
			dumpUsedTokens();
		}

		//  specific processor needed
		if (pSubProcessor != nullptr) {
			//  dump worldspaces
			if (pOptions->_worldspace == "l") {
				pSubProcessor->dumpWorldspaces();
			}
			//  dump vertex color map
			if (!pOptions->_fileNameC.empty()) {
				pSubProcessor->dumpVclrMap(pOptions->_fileNameC);
			}
			//  dump height map
			if (!pOptions->_fileNameH.empty()) {
				pSubProcessor->dumpVhgtMap(pOptions->_fileNameH);
			}
			//  dump texture map
			if (!pOptions->_fileNameL.empty()) {
				pSubProcessor->dumpVtexMap(pOptions->_fileNameL);
			}
			//  convert model
			if (!pOptions->_fileNameT.empty()) {
				convert(pOptions->_fileNameT, pOptions->_targetVersion, pOptions->_worldspace, pSubProcessor);
			}

			delete pSubProcessor;
		}
	}

	return isParsed;
}

//-----------------------------------------------------------------------------
bool TesProcessor::prepareRecordMap()
{
	verbose0("begin preparing");
	prepareRecordMapRecursive(_parser);
	verbose0("end preparing");
	return true;
}

//-----------------------------------------------------------------------------
bool TesProcessor::prepareRecordMapRecursive(vector<TesRecordBase*>& collection)
{
	for (auto& pRecord : collection) {
		switch (pRecord->_recordType) {
			case TesRecordType::RECORD:
				_mapRecords[pRecord->_name].push_back(pRecord);
				prepareRecordMapRecursive(*((TesRecordMain*) pRecord));
				break;

			case TesRecordType::RECORDGROUP:
				_mapRecords[pRecord->_name].push_back(pRecord);
				prepareRecordMapRecursive(*((TesRecordGroup*) pRecord));
				break;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
bool TesProcessor::parse(string const fileName)
{
	if (_parser.parse(fileName)) {
		return prepareRecordMap();
	}
	return false;
}

//-----------------------------------------------------------------------------
void TesProcessor::dumpTokensByName(string const token)
{
	if (token.empty()) {
		for (auto& mapEntry : _mapRecords) {
			for (auto& pRecord : mapEntry.second) {
				pRecord->dump(0);
			}
		}
	} else if (_mapRecords.count(token) > 0) {
		for (auto& pRecord : _mapRecords[token]) {
			pRecord->dump(0);
		}
	}
}

//-----------------------------------------------------------------------------
void TesProcessor::dumpTokensBySequence()
{
	for (auto& pRecord : _parser) {
		pRecord->dump(0);
	}
}

//-----------------------------------------------------------------------------
void TesProcessor::dumpTokensBySequenceAsXml()
{
	printf("<NodeStructure>\n");
	for (auto& pRecord : _parser) {
		pRecord->dumpXml();
	}
	printf("</NodeStructure>\n");
}

//-----------------------------------------------------------------------------
void TesProcessor::dumpUsedTokens()
{
	printf("\nUsed Tokens:\n");
	for (auto& mapEntry : _mapRecords) {
		printf(" - %s\t\t[%d]\n", mapEntry.first.c_str(), mapEntry.second.size());
	}
	printf("\n");
}

//-----------------------------------------------------------------------------
bool TesProcessor::convert(string const fileName, unsigned char const targetType, string const worldspace, ITesProcessor* pSubProcessor)
{
	bool	retVal(false);

	//  sanity check
	if (((_parser.fileType() == TesFileType::TES3) && (targetType == 3)) ||
		((_parser.fileType() == TesFileType::TES4) && (targetType == 4))) {
		verbose0("\x1B[33mCan't see any reason to convert TES%d into same version\033[0m", targetType);
		return false;
	}

	//  generate bitmap representing heights
	Bitmap*		pBitmapVHGT(pSubProcessor->generateVHGTBitmap());
	Bitmap*		pBitmapVCLR(pSubProcessor->generateVCLRBitmap());
	Bitmap*		pBitmapVTEX(pSubProcessor->generateVTEXBitmap());

	if ((pBitmapVHGT == nullptr) || (pBitmapVCLR == nullptr) || (pBitmapVTEX == nullptr)) {
		verbose0("\x1B[33mCan't generate intermediate height-bitmap - operation cancelled!\033[0m");
		return false;
	}

	//  delegate to converter
	switch (targetType) {
		case 3:	{		//  TES3
			verbose0("SORRY - not yet implemented!");
			break;
		}
		case 4: {		//  TES4
			Tes4Converter	converter(_mapRecords, _parser, worldspace);

			verbose0("begin converting");
			converter.convert(fileName, pBitmapVHGT, pBitmapVCLR, pBitmapVTEX);
			verbose0("end converting");
			break;
		}
	}

	//  clean up
	delete pBitmapVHGT;
	delete pBitmapVCLR;
	delete pBitmapVTEX;

	return retVal;
}
