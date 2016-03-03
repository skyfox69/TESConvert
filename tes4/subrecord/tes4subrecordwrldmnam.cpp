#include "tes4/subrecord/tes4subrecordwrldmnam.h"

//-----------------------------------------------------------------------------
Tes4SubRecordWRLDMNAM::Tes4SubRecordWRLDMNAM()
	:	TesRecordSub(TesFileType::TES4),
		_width       (0),
		_height      (0),
		_cellNwX     (0),
		_cellNwY     (0),
		_cellSeX     (0),
		_cellSeY     (0),
		_camHeightMin(0.0),
		_camHeightMax(0.0),
		_camInitPitch(0.0)
{
	_name = "MNAM";
	_size = 16;
}

//-----------------------------------------------------------------------------
Tes4SubRecordWRLDMNAM::Tes4SubRecordWRLDMNAM(unsigned char* pBuffer)
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
Tes4SubRecordWRLDMNAM::~Tes4SubRecordWRLDMNAM()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordWRLDMNAM::dump(const short depth)
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
void Tes4SubRecordWRLDMNAM::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" width=\"%d\"", _width);
	printf(" height=\"%d\"", _height);
	printf(" cellNwX=\"%5d\"", _cellNwX);
	printf(" cellNwY=\"%5d\"", _cellNwY);
	printf(" cellSeX=\"%5d\"", _cellSeX);
	printf(" cellSeY=\"%5d\"", _cellSeY);
	if (_size > 16) {
		printf(" camHeightMin=\"%f\"", _camHeightMin);
		printf(" camHeightMax=\"%f\"", _camHeightMax);
		printf(" camInitPitch=\"%f\"", _camInitPitch);
	}
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordWRLDMNAM::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordWRLDMNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordWRLDMNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDMNAM"] = Tes4SubRecordWRLDMNAM::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordWRLDMNAM::writeFile(FILE* pFile)
{
	writeString4(_name,    pFile);
	writeUShort4(_size,    pFile);
	writeULong  (_width,   pFile);
	writeULong  (_height,  pFile);
	writeShort  (_cellNwX, pFile);
	writeShort  (_cellNwY, pFile);
	writeShort  (_cellSeX, pFile);
	writeShort  (_cellSeY, pFile);
}