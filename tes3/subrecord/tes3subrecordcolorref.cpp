#include "tes3/subrecord/tes3subrecordcolorref.h"

//-----------------------------------------------------------------------------
Tes3SubRecordColorRef::Tes3SubRecordColorRef(unsigned char* pBuffer)
	:	Tes3SubRecordSingleULong(pBuffer)
{}

//-----------------------------------------------------------------------------
Tes3SubRecordColorRef::~Tes3SubRecordColorRef()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordColorRef::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  red::   0x%02X\n", indent.c_str(), ((_value)       & 0x000000FF));
	printf("%s  green:: 0x%02X\n", indent.c_str(), ((_value >>  8) & 0x000000FF));
	printf("%s  blue::  0x%02X\n", indent.c_str(), ((_value >> 16) & 0x000000FF));
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordColorRef::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordColorRef(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordColorRef::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["REGNCNAM"] = Tes3SubRecordColorRef::create;
	mapRecords["CELLNAM5"] = Tes3SubRecordColorRef::create;
}