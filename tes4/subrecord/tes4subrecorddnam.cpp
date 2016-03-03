#include "tes4/subrecord/tes4subrecorddnam.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordDNAM::Tes4SubRecordDNAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toUShort4(_size,   &pBuffer[4]);
		toFloat4 (_angle,  &pBuffer[6]);
		toULong  (_formId, &pBuffer[10]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDNAM::~Tes4SubRecordDNAM()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDNAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  angle::  %f\n", indent.c_str(), _angle);
	printf("%s  formId:: %ld\n", indent.c_str(), _formId);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDNAM::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" angle=\"%f\"", _angle);
	printf(" formId=\"%f\"", _formId);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDNAM::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["STATDNAM"] = Tes4SubRecordDNAM::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDNAM::writeFile(FILE* pFile)
{
}
