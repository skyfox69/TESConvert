#include "tes3/record/tes3recordignore.h"

//-----------------------------------------------------------------------------
Tes3RecordIgnore::Tes3RecordIgnore(unsigned char* pBuffer)
	:	TesRecordMain(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toSizeT  (_size,     &pBuffer[4]);
		toULong  (_unknownL, &pBuffer[8]);
		toULong  (_flags,    &pBuffer[12]);
	}
}

//-----------------------------------------------------------------------------
Tes3RecordIgnore::~Tes3RecordIgnore()
{}

//-----------------------------------------------------------------------------
size_t Tes3RecordIgnore::sizeRecord()
{
	return _size + 16;
}

//-----------------------------------------------------------------------------
size_t Tes3RecordIgnore::sizeTotal()
{
	return sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3RecordIgnore::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s\x1B[1;35mTemp. ignored:: %s\033[0m\n", indent.c_str(), _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3RecordIgnore::create(unsigned char* pBuffer)
{
	return new Tes3RecordIgnore(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3RecordIgnore::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CLAS"] = Tes3RecordIgnore::create;
	mapRecords["FACT"] = Tes3RecordIgnore::create;
	mapRecords["RACE"] = Tes3RecordIgnore::create;
	mapRecords["SOUN"] = Tes3RecordIgnore::create;
	mapRecords["SKIL"] = Tes3RecordIgnore::create;
	mapRecords["MGEF"] = Tes3RecordIgnore::create;
	mapRecords["SCPT"] = Tes3RecordIgnore::create;
	mapRecords["BSGN"] = Tes3RecordIgnore::create;
	mapRecords["STAT"] = Tes3RecordIgnore::create;
	mapRecords["DOOR"] = Tes3RecordIgnore::create;
	mapRecords["MISC"] = Tes3RecordIgnore::create;
	mapRecords["WEAP"] = Tes3RecordIgnore::create;
	mapRecords["CONT"] = Tes3RecordIgnore::create;
	mapRecords["SPEL"] = Tes3RecordIgnore::create;
	mapRecords["CREA"] = Tes3RecordIgnore::create;
	mapRecords["BODY"] = Tes3RecordIgnore::create;
	mapRecords["LIGH"] = Tes3RecordIgnore::create;
	mapRecords["ENCH"] = Tes3RecordIgnore::create;
	mapRecords["NPC_"] = Tes3RecordIgnore::create;
	mapRecords["ARMO"] = Tes3RecordIgnore::create;
	mapRecords["CLOT"] = Tes3RecordIgnore::create;
	mapRecords["REPA"] = Tes3RecordIgnore::create;
	mapRecords["ACTI"] = Tes3RecordIgnore::create;
	mapRecords["APPA"] = Tes3RecordIgnore::create;
	mapRecords["LOCK"] = Tes3RecordIgnore::create;
	mapRecords["PROB"] = Tes3RecordIgnore::create;
	mapRecords["INGR"] = Tes3RecordIgnore::create;
	mapRecords["BOOK"] = Tes3RecordIgnore::create;
	mapRecords["ALCH"] = Tes3RecordIgnore::create;
	mapRecords["LEVI"] = Tes3RecordIgnore::create;
	mapRecords["LEVC"] = Tes3RecordIgnore::create;
	mapRecords["PGRD"] = Tes3RecordIgnore::create;
	mapRecords["SNDG"] = Tes3RecordIgnore::create;
	mapRecords["DIAL"] = Tes3RecordIgnore::create;
	mapRecords["INFO"] = Tes3RecordIgnore::create;
	mapRecords["SSCR"] = Tes3RecordIgnore::create;
}

//-----------------------------------------------------------------------------
void Tes3RecordIgnore::writeFile(FILE* pFile)
{}