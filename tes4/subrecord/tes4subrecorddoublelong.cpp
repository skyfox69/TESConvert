#include "tes4/subrecord/tes4subrecorddoublelong.h"

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleLong::Tes4SubRecordDoubleLong(string const name, long const value1, long const value2)
	:	TesRecordSub(TesFileType::TES4)
{
	_name     = name;
	_size     = 8;
	_value[0] = value1;
	_value[1] = value2;
}

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleLong::Tes4SubRecordDoubleLong(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toLong   (_value[0], &pBuffer[6]);
		toLong   (_value[1], &pBuffer[10]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleLong::~Tes4SubRecordDoubleLong()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleLong::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  [0]:: %d\n", indent.c_str(), _value[0]);
	printf("%s  [1]:: %d\n", indent.c_str(), _value[1]);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleLong::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value1=\"%d\" value2=\"%d\"", _value[0], _value[1]);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDoubleLong::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDoubleLong(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleLong::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDNAM0"] = Tes4SubRecordDoubleLong::create;
	mapRecords["WRLDNAM9"] = Tes4SubRecordDoubleLong::create;
	mapRecords["TES4DATA"] = Tes4SubRecordDoubleLong::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleLong::writeFile(FILE* pFile)
{
	writeString4(_name,     pFile);
	writeUShort4(_size,     pFile);
	writeLong   (_value[0], pFile);
	writeLong   (_value[1], pFile);
}
