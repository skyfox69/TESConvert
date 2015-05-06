#include "tes4/subrecord/tes4subrecordsinglestring.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleString::Tes4SubRecordSingleString(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toUShort4(_size, &pBuffer[4]);
		toStringN(_text, &pBuffer[6], _size);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleString::~Tes4SubRecordSingleString()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %s\n", indent.c_str(), _text.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleString::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleString(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4CNAM"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDFULL"] = Tes4SubRecordSingleString::create;
}
