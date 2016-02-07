#include "tes4/subrecord/tes4subrecordxxxx.h"

//-----------------------------------------------------------------------------
Tes4SubRecordXXXX::Tes4SubRecordXXXX(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toUShort4(_size,     &pBuffer[4]);
		toULong  (_dataSize, &pBuffer[6]);

		_size = _dataSize + 10;
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordXXXX::~Tes4SubRecordXXXX()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordXXXX::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  size:: %d - 0x08X\n", indent.c_str(), _size, _size);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordXXXX::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes size=\"%d - 0x08X\"", _size, _size);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordXXXX::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordXXXX(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordXXXX::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDXXXX"] = Tes4SubRecordXXXX::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordXXXX::writeFile(FILE* pFile)
{
}