#include "tes4/subrecord/tes4subrecordrefrdata.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordREFRDATA::Tes4SubRecordREFRDATA(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toUShort4(_size, &pBuffer[4]);
		toFloat4 (_posX, &pBuffer[6]);
		toFloat4 (_posY, &pBuffer[10]);
		toFloat4 (_posZ, &pBuffer[14]);
		toFloat4 (_rotX, &pBuffer[18]);
		toFloat4 (_rotY, &pBuffer[22]);
		toFloat4 (_rotZ, &pBuffer[26]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordREFRDATA::~Tes4SubRecordREFRDATA()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordREFRDATA::dump(const short depth)
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
void Tes4SubRecordREFRDATA::dumpXml()
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
TesRecordBase* Tes4SubRecordREFRDATA::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordREFRDATA(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordREFRDATA::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["REFRDATA"] = Tes4SubRecordREFRDATA::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordREFRDATA::writeFile(FILE* pFile)
{
}
