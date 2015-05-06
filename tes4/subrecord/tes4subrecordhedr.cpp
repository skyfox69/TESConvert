#include "tes4/subrecord/tes4subrecordhedr.h"

//-----------------------------------------------------------------------------
Tes4SubRecordHEDR::Tes4SubRecordHEDR(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,         pBuffer);
		toUShort4(_size,         &pBuffer[4]);
		toFloat4 (_version,      &pBuffer[6]);
		toULong  (_numRecords,   &pBuffer[10]);
		toULong  (_nextObjectId, &pBuffer[14]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordHEDR::~Tes4SubRecordHEDR()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  version::      %.2f\n", indent.c_str(), _version);
	printf("%s  numRecords::   %d\n", indent.c_str(), _numRecords);
	printf("%s  nextObjectId:: %d\n", indent.c_str(), _nextObjectId);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordHEDR::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordHEDR(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4HEDR"] = Tes4SubRecordHEDR::create;
}