#include "tes4/subrecord/tes4subrecordvhgt.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordVHGT::Tes4SubRecordVHGT(float const offset)
	:	TesRecordSub(TesFileType::TES4),
		_offset(offset)
{
	_name = "VHGT";
	_size = 1096;
	_unknown[0] = 0;
	_unknown[1] = 0;
	_unknown[2] = 0;
	memset(_height, 0, 33*33*sizeof(unsigned char));
}

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
/**/
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

//-----------------------------------------------------------------------------
void Tes4SubRecordVHGT::writeFile(FILE* pFile)
{
	writeString4(_name,  pFile);
	writeUShort4(_size,  pFile);
	writeFloat4 (_offset, pFile);
	fwrite(_height, 1, 33*33, pFile);
	fwrite(_unknown, 1, 3, pFile);
}

//-----------------------------------------------------------------------------
unsigned char* Tes4SubRecordVHGT::writeMem(unsigned char* pMemory)
{
	pMemory += writeString4(_name,   pMemory);
	pMemory += writeUShort4(_size,   pMemory);
	pMemory += writeFloat4 (_offset, pMemory);
	memcpy(pMemory, _height, 33*33*sizeof(unsigned char));
	memcpy(pMemory, _unknown, 3*sizeof(unsigned char));
	return (pMemory + 33*33+3);
}