#include "common/tesprocessor.h"
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
		//  dump token structure by token name
		if (pOptions->_dumpFinalT) {
			dumpTokensByName();
		}
		//  dump token structure by file occurancy
		if (pOptions->_dumpFinalS) {
			dumpTokensBySequence();
		}
		//  dump vertex color map
		if (!pOptions->_fileNameC.empty()) {
			dumpVclrMap(pOptions->_fileNameC);
		}
		//  dump height map
		if (!pOptions->_fileNameH.empty()) {
			dumpVhgtMap(pOptions->_fileNameH);
		}
		//  dump texture map
		if (!pOptions->_fileNameL.empty()) {
			dumpVtexMap(pOptions->_fileNameL);
		}
		//  convert to TES4
		if (!pOptions->_fileNameT.empty() && (pOptions->_targetVersion == 4)) {
			convertToTES4(pOptions->_fileNameT);
		}
		
	}

	return isParsed;
}

//-----------------------------------------------------------------------------
bool TesProcessor::prepareRecordMap()
{
	printf("begin preparing\n");
	prepareRecordMapRecursive(_parser);
	printf("end preparing\n");
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
bool TesProcessor::dumpVclrMap(string const fileName)
{
	switch (_parser.fileType()) {
		case TesFileType::TES3:
		{
			Tes3Processor	subProcessor(_mapRecords);
			return subProcessor.dumpVclrMap(fileName);
		}
		case TesFileType::TES4:
		{
			Tes4Processor	subProcessor(_mapRecords, _parser);
			return subProcessor.dumpVclrMap(fileName);
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
bool TesProcessor::dumpVhgtMap(string const fileName)
{
	switch (_parser.fileType()) {
		case TesFileType::TES3:
		{
			Tes3Processor	subProcessor(_mapRecords);
			return subProcessor.dumpVhgtMap(fileName);
		}
		case TesFileType::TES4:
		{
			Tes4Processor	subProcessor(_mapRecords, _parser);
			return subProcessor.dumpVhgtMap(fileName);
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
bool TesProcessor::dumpVtexMap(string const fileName)
{
	switch (_parser.fileType()) {
		case TesFileType::TES3:
		{
			Tes3Processor	subProcessor(_mapRecords);
			return subProcessor.dumpVtexMap(fileName);
		}
		case TesFileType::TES4:
		{
			Tes4Processor	subProcessor(_mapRecords, _parser);
			return subProcessor.dumpVtexMap(fileName);
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
bool TesProcessor::convertToTES4(const string fileName)
{
	
	
	
	return true;
}