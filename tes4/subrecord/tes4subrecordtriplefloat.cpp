#include "tes4/subrecord/tes4subrecordtriplefloat.h"

//-----------------------------------------------------------------------------
Tes4SubRecordTripleFloat::Tes4SubRecordTripleFloat(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_value1     (0),
		_value2     (0),
		_value3     (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toUShort4(_size,   &pBuffer[4]);
		toFloat4 (_value1, &pBuffer[6]);
		toFloat4 (_value2, &pBuffer[10]);
		toFloat4 (_value3, &pBuffer[10]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordTripleFloat::~Tes4SubRecordTripleFloat()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordTripleFloat::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %f, %f, %f - (0x%02X, 0x%02X, 0x%02X)\n", indent.c_str(),
			_value1, _value2, _value3, ((int) (_value1*255)), ((int) (_value2*255)), ((int) (_value3*255)));
}

//-----------------------------------------------------------------------------
void Tes4SubRecordTripleFloat::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value1=\"%f\" value2=\"%f\" value3=\"%f\"", _value1, _value2, _value3);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordTripleFloat::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordTripleFloat(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordTripleFloat::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["MATTCNAM"] = Tes4SubRecordTripleFloat::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordTripleFloat::writeFile(FILE* pFile)
{
}