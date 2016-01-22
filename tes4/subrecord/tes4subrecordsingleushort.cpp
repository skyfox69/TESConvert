#include "tes4/subrecord/tes4subrecordsingleushort.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleUShort::Tes4SubRecordSingleUShort(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_value      (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		if (_size == 1) {
			unsigned char	tmp(0);

			toChar(tmp, &pBuffer[6]);
			_value = tmp;
		} else {
			toUShort(_value, &pBuffer[6]);
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleUShort::~Tes4SubRecordSingleUShort()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleUShort::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%04X\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleUShort::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleUShort(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleUShort::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLDATA"] = Tes4SubRecordSingleUShort::create;
	mapRecords["TXSTDNAM"] = Tes4SubRecordSingleUShort::create;
	mapRecords["CELLXNAM"] = Tes4SubRecordSingleUShort::create;
	mapRecords["WRLDPNAM"] = Tes4SubRecordSingleUShort::create;
}
