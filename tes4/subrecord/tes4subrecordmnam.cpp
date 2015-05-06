#include "tes4/subrecord/tes4subrecordmnam.h"

//-----------------------------------------------------------------------------
Tes4SubRecordMNAM::Tes4SubRecordMNAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,    pBuffer);
		toUShort4(_size,    &pBuffer[4]);
		toULong  (_width,   &pBuffer[6]);
		toULong  (_height,  &pBuffer[10]);
		toShort  (_cellNwX, &pBuffer[14]);
		toShort  (_cellNwY, &pBuffer[16]);
		toShort  (_cellSeX, &pBuffer[18]);
		toShort  (_cellSeY, &pBuffer[20]);
		if (_size > 16) {
			toFloat4 (_camHeightMin, &pBuffer[22]);
			toFloat4 (_camHeightMax, &pBuffer[26]);
			toFloat4 (_camInitPitch, &pBuffer[30]);
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordMNAM::~Tes4SubRecordMNAM()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordMNAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  width::   %d\n", indent.c_str(), _width);
	printf("%s  height::  %d\n", indent.c_str(), _height);
	printf("%s  cellNwX:: %5d\n", indent.c_str(), _cellNwX);
	printf("%s  cellNwY:: %5d\n", indent.c_str(), _cellNwY);
	printf("%s  cellSeX:: %5d\n", indent.c_str(), _cellSeX);
	printf("%s  cellSeY:: %5d\n", indent.c_str(), _cellSeY);
	if (_size > 16) {
		printf("%s  camHeightMin:: %f\n", indent.c_str(), _camHeightMin);
		printf("%s  camHeightMax:: %f\n", indent.c_str(), _camHeightMax);
		printf("%s  camInitPitch:: %f\n", indent.c_str(), _camInitPitch);
	}
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordMNAM::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordMNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordMNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDMNAM"] = Tes4SubRecordMNAM::create;
}
