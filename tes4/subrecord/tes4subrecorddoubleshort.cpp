#include "tes4/subrecord/tes4subrecorddoubleshort.h"

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleShort::Tes4SubRecordDoubleShort(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_value1     (0),
		_value2     (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toShort  (_value1, &pBuffer[6]);
		toShort  (_value2, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleShort::~Tes4SubRecordDoubleShort()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleShort::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  value1/x:: 0x%08X - %d\n", indent.c_str(), _value1, _value1);
	printf("%s  value2/x:: 0x%08X - %d\n", indent.c_str(), _value2, _value2);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleShort::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value1=\"0x%08X - %d\" value2=\"0x%08X - %d\"", _value1, _value1, _value2, _value2);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDoubleShort::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDoubleShort(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleShort::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDWCTR"] = Tes4SubRecordDoubleShort::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleShort::writeFile(FILE* pFile)
{
}