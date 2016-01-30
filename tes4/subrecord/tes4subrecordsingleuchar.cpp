#include "tes4/subrecord/tes4subrecordsingleuchar.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleUChar::Tes4SubRecordSingleUChar(string const name, unsigned char const value)
	:	TesRecordSub(TesFileType::TES4),
		_value(value)
{
	_name = name;
	_size = 1;
}

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
void Tes4SubRecordSingleUChar::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value=\"0x%02X\"", _value);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
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
	mapRecords["LTEXSNAM"] = Tes4SubRecordSingleUChar::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleUChar::writeFile(FILE* pFile)
{
	writeString4(_name,  pFile);
	writeUShort4(_size,  pFile);
	writeChar   (_value, pFile);
}