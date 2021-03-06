#include "tes3/subrecord/tes3subrecordsingleulong.h"

//-----------------------------------------------------------------------------
Tes3SubRecordSingleULong::Tes3SubRecordSingleULong(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toULong (_value, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordSingleULong::~Tes3SubRecordSingleULong()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleULong::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %d, 0x%08x\n", indent.c_str(), _value, _value);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleULong::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" value=\"%d\"", _value);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordSingleULong::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordSingleULong(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleULong::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["GMSTINTV"] = Tes3SubRecordSingleULong::create;
	mapRecords["LTEXINTV"] = Tes3SubRecordSingleULong::create;
	mapRecords["LANDDATA"] = Tes3SubRecordSingleULong::create;
	mapRecords["CELLNAM0"] = Tes3SubRecordSingleULong::create;
	mapRecords["FRMRNAM0"] = Tes3SubRecordSingleULong::create;
	mapRecords["FRMRINTV"] = Tes3SubRecordSingleULong::create;
	mapRecords["FRMRINDX"] = Tes3SubRecordSingleULong::create;
	mapRecords["CELLINTV"] = Tes3SubRecordSingleULong::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleULong::writeFile(FILE* pFile)
{}