#include "tes4/subrecord/tes4subrecordsingleulong.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleULong::Tes4SubRecordSingleULong(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toULong  (_value, &pBuffer[6]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleULong::Tes4SubRecordSingleULong(string const name, unsigned long const value)
	:	TesRecordSub(TesFileType::TES4),
		_value(value)
{
	_name = name;
	_size = 4;
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleULong::~Tes4SubRecordSingleULong()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%08X - %d\n", indent.c_str(), _value, _value);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes value=\"0x%08X - %d\"", _value, _value);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleULong::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleULong(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["WRLDNAM2"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDNAM3"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDCNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDZNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDXLCN"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDWNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDLTMP"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDXEZN"] = Tes4SubRecordSingleULong::create;
	mapRecords["TES4INTV"] = Tes4SubRecordSingleULong::create;
	mapRecords["TES4INCC"] = Tes4SubRecordSingleULong::create;
	mapRecords["LTEXTNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["LTEXMNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["LTEXGNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLLTMP"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXCIM"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXLCN"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXCMO"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXEZN"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXCAS"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXCCM"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXOWN"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXILL"] = Tes4SubRecordSingleULong::create;
	mapRecords["WRLDFULL"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLFULL"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXCWT"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLLNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXWCN"] = Tes4SubRecordSingleULong::create;
	mapRecords["CELLXWCS"] = Tes4SubRecordSingleULong::create;
	mapRecords["MATTHNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["MATTPNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRNAME"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXLRM"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXEMI"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXLIB"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXOWN"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXLRT"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXMBR"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXTRI"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXACT"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXLCM"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRLNAM"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXPWR"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXWCN"] = Tes4SubRecordSingleULong::create;
	mapRecords["REFRXEZN"] = Tes4SubRecordSingleULong::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleULong::writeFile(FILE* pFile)
{
	writeString4(_name,  pFile);
	writeUShort4(_size,  pFile);
	writeULong  (_value, pFile);
}

//-----------------------------------------------------------------------------
unsigned char* Tes4SubRecordSingleULong::writeMem(unsigned char* pMemory)
{
	pMemory += writeString4(_name,  pMemory);
	pMemory += writeUShort4(_size,  pMemory);
	pMemory += writeULong  (_value, pMemory);
	return pMemory;
}