#include "common/tesprocessor.h"
#include "record/tesrecordbase.h"
#include "tes3/tes3processor.h"
#include <cstring>

//-----------------------------------------------------------------------------
TesProcessor::TesProcessor()
{}

//-----------------------------------------------------------------------------
TesProcessor::~TesProcessor()
{}

//-----------------------------------------------------------------------------
bool TesProcessor::prepareRecordMap()
{
	printf("begin preparing\n");
	for (auto& pRecord : _parser) {
		_mapRecords[pRecord->_name].push_back(pRecord);
	}
	printf("end preparing\n");
	
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
//			Tes3Processor	subProcessor;
//			return subProcessor.dumpVclrMap(fileName, _mapRecords);
			return true;
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
//			Tes3Processor	subProcessor;
//			return subProcessor.dumpVhgtMap(fileName, _mapRecords);
			return true;
		}
	}
	return false;
}
