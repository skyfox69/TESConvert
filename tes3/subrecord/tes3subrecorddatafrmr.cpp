#include "tes3/subrecord/tes3subrecorddatafrmr.h"

//-----------------------------------------------------------------------------
Tes3SubRecordDATAFRMR::Tes3SubRecordDATAFRMR(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toSizeT  (_size, &pBuffer[4]);
		toFloat4 (_posX, &pBuffer[8]);
		toFloat4 (_posY, &pBuffer[12]);
		toFloat4 (_posZ, &pBuffer[16]);
		toFloat4 (_rotX, &pBuffer[20]);
		toFloat4 (_rotY, &pBuffer[24]);
		toFloat4 (_rotZ, &pBuffer[28]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordDATAFRMR::~Tes3SubRecordDATAFRMR()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATAFRMR::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  posX:: %f\n", indent.c_str(), _posX);
	printf("%s  posY:: %f\n", indent.c_str(), _posY);
	printf("%s  posZ:: %f\n", indent.c_str(), _posZ);
	printf("%s  rotX:: %f\n", indent.c_str(), _rotX);
	printf("%s  rotY:: %f\n", indent.c_str(), _rotY);
	printf("%s  rotZ:: %f\n", indent.c_str(), _rotZ);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATAFRMR::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" posX=\"%f\"", _posX);
	printf(" posY=\"%f\"", _posY);
	printf(" posZ=\"%f\"", _posZ);
	printf(" rotX=\"%f\"", _rotX);
	printf(" rotY=\"%f\"", _rotY);
	printf(" rotZ=\"%f\"", _rotZ);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordDATAFRMR::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordDATAFRMR(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATAFRMR::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["FRMRDATA"] = Tes3SubRecordDATAFRMR::create;
	mapRecords["FRMRDODT"] = Tes3SubRecordDATAFRMR::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATAFRMR::writeFile(FILE* pFile)
{}