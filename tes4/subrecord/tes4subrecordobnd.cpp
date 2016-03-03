#include "tes4/subrecord/tes4subrecordobnd.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordOBND::Tes4SubRecordOBND()
	:	TesRecordSub(TesFileType::TES4),
		_x1(0),
		_y1(0),
		_z1(0),
		_x2(0),
		_y2(0),
		_z2(0)
{
	_name = "OBND";
	_size = 12;
}

//-----------------------------------------------------------------------------
Tes4SubRecordOBND::Tes4SubRecordOBND(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toUShort4(_size, &pBuffer[4]);
		toShort  (_x1,   &pBuffer[6]);
		toShort  (_y1,   &pBuffer[8]);
		toShort  (_z1,   &pBuffer[10]);
		toShort  (_x2,   &pBuffer[12]);
		toShort  (_y2,   &pBuffer[14]);
		toShort  (_z2,   &pBuffer[16]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordOBND::~Tes4SubRecordOBND()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  bounds:: %d,%d,%d - %d,%d,%d\n", indent.c_str(), _x1, _y1, _z1, _x2, _y2, _z2);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordOBND::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordOBND(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TXSTOBND"] = Tes4SubRecordOBND::create;
	mapRecords["STATOBND"] = Tes4SubRecordOBND::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::writeFile(FILE* pFile)
{
	writeString4(_name, pFile);
	writeUShort4(_size, pFile);
	writeShort  (_x1,   pFile);
	writeShort  (_y1,   pFile);
	writeShort  (_z1,   pFile);
	writeShort  (_x2,   pFile);
	writeShort  (_y2,   pFile);
	writeShort  (_z2,   pFile);
}