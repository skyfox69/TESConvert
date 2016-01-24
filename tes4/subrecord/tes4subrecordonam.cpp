#include "tes4/subrecord/tes4subrecordonam.h"

//-----------------------------------------------------------------------------
Tes4SubRecordONAM::Tes4SubRecordONAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,    pBuffer);
		toUShort4(_size,    &pBuffer[4]);
		toFloat4 (_scale,   &pBuffer[6]);
		toFloat4 (_offsetX, &pBuffer[10]);
		toFloat4 (_offsetY, &pBuffer[14]);
		toFloat4 (_offsetZ, &pBuffer[18]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordONAM::~Tes4SubRecordONAM()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordONAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  scale::   %f\n", indent.c_str(), _scale);
	printf("%s  offsetX:: %f\n", indent.c_str(), _offsetX);
	printf("%s  offsetY:: %f\n", indent.c_str(), _offsetY);
	printf("%s  offsetZ:: %f\n", indent.c_str(), _offsetZ);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordONAM::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" scale=\"%f\"", _scale);
	printf(" offsetX=\"%f\"", _offsetX);
	printf(" offsetY=\"%f\"", _offsetY);
	printf(" offsetZ=\"%f\"", _offsetZ);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordONAM::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordONAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordONAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDONAM"] = Tes4SubRecordONAM::create;
}
