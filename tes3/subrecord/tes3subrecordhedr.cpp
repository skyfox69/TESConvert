#include "tes3/subrecord/tes3subrecordhedr.h"

//-----------------------------------------------------------------------------
Tes3SubRecordHEDR::Tes3SubRecordHEDR(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,        pBuffer);
		toSizeT  (_size,        &pBuffer[4]);
		toFloat4 (_version,     &pBuffer[8]);
		toULong  (_unknown,     &pBuffer[12]);
		toStringN(_company,     &pBuffer[16], 32);
		toStringN(_description, &pBuffer[48], 256);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordHEDR::~Tes3SubRecordHEDR()
{}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordHEDR::sizeRecord()
{
	return 8;
}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordHEDR::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3SubRecordHEDR::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  version::     %.2f\n", indent.c_str(), _version);
	printf("%s  company::     %s\n", indent.c_str(), _company.c_str());
	printf("%s  description:: %s\n", indent.c_str(), _description.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordHEDR::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordHEDR(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordHEDR::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES3HEDR"] = Tes3SubRecordHEDR::create;
}