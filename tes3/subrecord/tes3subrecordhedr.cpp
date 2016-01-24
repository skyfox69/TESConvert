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
void Tes3SubRecordHEDR::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  version::     %.2f\n", indent.c_str(), _version);
	printf("%s  company::     %s\n", indent.c_str(), _company.c_str());
	printf("%s  description:: %s\n", indent.c_str(), _description.c_str());
}

//-----------------------------------------------------------------------------
void Tes3SubRecordHEDR::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" version=\"%.2f\"", _version);
	printf(" company=\"%s\"", _company.c_str());
	printf(" description=\"%s\"", _description.c_str());
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
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