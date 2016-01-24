#include "tes4/subrecord/tes4subrecordvhgt.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordVHGT::Tes4SubRecordVHGT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toUShort4(_size,   &pBuffer[4]);
		toFloat4 (_offset, &pBuffer[6]);
		memcpy(_height, &(pBuffer[10]), 33*33*sizeof(unsigned char));
		pBuffer += 10 + 33*33*sizeof(unsigned char);
		_unknown[0] = pBuffer[0];
		_unknown[1] = pBuffer[1];
		_unknown[2] = pBuffer[2];
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordVHGT::~Tes4SubRecordVHGT()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordVHGT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  offset::  %f\n", indent.c_str(), _offset);
	printf("%s  height::\n", indent.c_str());
/**
	for (short i(0); i < 33; ++i) {
		printf("%s    ", indent.c_str());
		for (short j(0); j < 33; ++j) {
			printf("%02X,", _height[i][j]);
		}
		printf("\n");
	}
	printf("%s  unknown:: 0x%02X,0x%02X,0x%02X\n", indent.c_str(), _unknown[0], _unknown[1], _unknown[2]);
/**/
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVHGT::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes offset=\"%f\"", _offset);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordVHGT::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordVHGT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVHGT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVHGT"] = Tes4SubRecordVHGT::create;
}
