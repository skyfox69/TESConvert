#include "tes3/subrecord/tes3subrecordvhgt.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes3SubRecordVHGT::Tes3SubRecordVHGT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toSizeT  (_size,   &pBuffer[4]);
		toFloat4 (_offset, &pBuffer[8]);
		memcpy(_height, &(pBuffer[12]), 65*65*sizeof(unsigned char));
		pBuffer += 12 + 65*65*sizeof(unsigned char);
		_unknown[0] = pBuffer[0];
		_unknown[1] = pBuffer[1];
		_unknown[2] = pBuffer[2];
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordVHGT::~Tes3SubRecordVHGT()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordVHGT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  offset::  %f\n", indent.c_str(), _offset);
	printf("%s  height::\n", indent.c_str());
	for (short i(0); i < 65; ++i) {
		printf("%s    ", indent.c_str());
		for (short j(0); j < 65; ++j) {
			printf("%02X,", _height[i][j]);
		}
		printf("\n");
	}
	printf("%s  unknown:: 0x%02X,0x%02X,0x%02X\n", indent.c_str(), _unknown[0], _unknown[1], _unknown[2]);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVHGT::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" offset=\"%f\"", _offset);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordVHGT::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordVHGT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVHGT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVHGT"] = Tes3SubRecordVHGT::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVHGT::writeFile(FILE* pFile)
{}
