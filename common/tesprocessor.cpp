#include "common/tesprocessor.h"
#include "common/itesprocessor.h"
#include "common/util/tesoptions.h"
#include "record/tesrecordbase.h"
#include "tes3/tes3processor.h"
#include "tes4/tes4processor.h"
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
			dumpTokensByName();
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
			//  convert to TES4
			if (!pOptions->_fileNameT.empty() && (pOptions->_targetVersion == 4)) {
				convertToTES4(pOptions->_fileNameT);
			}
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
void TesProcessor::dumpTokensByName()
{
	for (auto& mapEntry : _mapRecords) {
		for (auto& pRecord : mapEntry.second) {
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
bool TesProcessor::convertToTES4(const string fileName)
{
	
	
	
	return true;
}
