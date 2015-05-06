#include "tes4/subrecord/tes4subrecordsingleuchar.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleUChar::Tes4SubRecordSingleUChar(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toChar(  _value,  &pBuffer[6]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleUChar::~Tes4SubRecordSingleUChar()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleUChar::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%02X\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleUChar::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleUChar(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleUChar::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDDATA"] = Tes4SubRecordSingleUChar::create;
}
