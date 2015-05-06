#include "tes4/subrecord/tes4subrecordsingleulong.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleULong::Tes4SubRecordSingleULong(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toULong  (_value, &pBuffer[6]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleULong::~Tes4SubRecordSingleULong()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %d\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleULong::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleULong(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDNAM2"] = Tes4SubRecordSingleULong::create;
}
