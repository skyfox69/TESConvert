#include "tes4/subrecord/tes4subrecordsinglefloat.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleFloat::Tes4SubRecordSingleFloat(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_valueLong  (0),
		_value      (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,      pBuffer);
		toUShort4(_size,      &pBuffer[4]);
		toFloat4 (_value,     &pBuffer[6]);
		toULong  (_valueLong, &pBuffer[6]);

		if ((_valueLong != 0x7F7FFFFF) && (_valueLong != 0x4F7FFFC9)) {
			_valueLong = 0;
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleFloat::~Tes4SubRecordSingleFloat()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleFloat::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	if (_valueLong != 0) {
		printf("%s  0x%08X\n", indent.c_str(), _valueLong);
	} else {
		printf("%s  %f\n", indent.c_str(), _value);
	}
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleFloat::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes ");
	if (_valueLong != 0) {
		printf(" value=\"0x%08X\"", _valueLong);
	} else {
		printf(" value=\"%f\"", _value);
	}
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleFloat::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleFloat(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleFloat::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLXCLW"] = Tes4SubRecordSingleFloat::create;
	mapRecords["WRLDNAM4"] = Tes4SubRecordSingleFloat::create;
	mapRecords["WRLDNAMA"] = Tes4SubRecordSingleFloat::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleFloat::writeFile(FILE* pFile)
{
}