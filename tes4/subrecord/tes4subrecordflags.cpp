#include "tes4/subrecord/tes4subrecordflags.h"

//-----------------------------------------------------------------------------
Tes4SubRecordFlags::Tes4SubRecordFlags(string const name, unsigned long const value)
	:	Tes4SubRecordSingleULong(name, value)
{}

//-----------------------------------------------------------------------------
Tes4SubRecordFlags::Tes4SubRecordFlags(unsigned char* pBuffer)
	:	Tes4SubRecordSingleULong(pBuffer)
{}

//-----------------------------------------------------------------------------
Tes4SubRecordFlags::~Tes4SubRecordFlags()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordFlags::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%08X\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordFlags::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value=\"0x%08X\"", _value);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordFlags::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordFlags(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordFlags::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDDATA"] = Tes4SubRecordFlags::create;
}