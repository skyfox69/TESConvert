#include "tes3/subrecord/tes3subrecordsinglestring.h"

//-----------------------------------------------------------------------------
Tes3SubRecordSingleString::Tes3SubRecordSingleString(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toSizeT  (_size, &pBuffer[4]);
		toStringN(_text, &pBuffer[8], _size);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordSingleString::~Tes3SubRecordSingleString()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleString::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %s\n", indent.c_str(), _text.c_str());
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleString::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" text=\"%s\"", _text.c_str());
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordSingleString::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordSingleString(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleString::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["GMSTNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["GMSTSTRV"] = Tes3SubRecordSingleString::create;
	mapRecords["GLOBNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["GLOBFNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["REGNNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["REGNFNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["REGNBNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["LTEXNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["LTEXDATA"] = Tes3SubRecordSingleString::create;
	mapRecords["CELLNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["CELLRGNN"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRNAME"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRDNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRANAM"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRKNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRCNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRTNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRXSOL"] = Tes3SubRecordSingleString::create;
	mapRecords["FRMRBNAM"] = Tes3SubRecordSingleString::create;
	mapRecords["TES3MAST"] = Tes3SubRecordSingleString::create;
}
