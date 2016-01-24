#include "tes4/subrecord/tes4subrecorddoubleuchar.h"

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleUChar::Tes4SubRecordDoubleUChar(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toChar(  _value1, &pBuffer[6]);
		toChar(  _value2, &pBuffer[7]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleUChar::~Tes4SubRecordDoubleUChar()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleUChar::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%02X\n", indent.c_str(), _value1);
	printf("%s  0x%02X\n", indent.c_str(), _value2);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleUChar::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value1=\"0x%02X\" value2=\"0x%02X\"", _value1, _value2);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDoubleUChar::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDoubleUChar(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleUChar::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LTEXHNAM"] = Tes4SubRecordDoubleUChar::create;
}
