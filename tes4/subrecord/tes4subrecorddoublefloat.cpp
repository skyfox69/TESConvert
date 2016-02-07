#include "tes4/subrecord/tes4subrecorddoublefloat.h"

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleFloat::Tes4SubRecordDoubleFloat(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_value1     (0),
		_value2     (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toUShort4(_size,   &pBuffer[4]);
		toFloat4 (_value1, &pBuffer[6]);
		toFloat4 (_value2, &pBuffer[10]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDoubleFloat::~Tes4SubRecordDoubleFloat()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleFloat::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  value1:: %f\n", indent.c_str(), _value1);
	printf("%s  value2:: %f\n", indent.c_str(), _value2);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleFloat::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value1=\"%f\" value2=\"%f\"", _value1, _value2);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDoubleFloat::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDoubleFloat(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleFloat::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDDNAM"] = Tes4SubRecordDoubleFloat::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDoubleFloat::writeFile(FILE* pFile)
{
}