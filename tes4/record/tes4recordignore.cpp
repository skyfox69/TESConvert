#include "tes4/record/tes4recordignore.h"

//-----------------------------------------------------------------------------
Tes4RecordIgnore::Tes4RecordIgnore(unsigned char* pBuffer)
	:	TesRecordMain(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toSizeT  (_size,     &pBuffer[4]);
		toULong  (_flags,    &pBuffer[8]);
		toULong  (_id,       &pBuffer[12]);
		toULong  (_revision, &pBuffer[16]);
		toUShort (_version,  &pBuffer[20]);
		toUShort (_unknownS, &pBuffer[22]);
	}
}

//-----------------------------------------------------------------------------
Tes4RecordIgnore::~Tes4RecordIgnore()
{}

//-----------------------------------------------------------------------------
size_t Tes4RecordIgnore::sizeRecord()
{
	return _size + 24;
}

//-----------------------------------------------------------------------------
size_t Tes4RecordIgnore::sizeTotal()
{
	return sizeRecord();
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4RecordIgnore::create(unsigned char* pBuffer)
{
	return new Tes4RecordIgnore(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4RecordIgnore::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["GMST"] = Tes4RecordIgnore::create;
	mapRecords["KYWD"] = Tes4RecordIgnore::create;
	mapRecords["LCRT"] = Tes4RecordIgnore::create;
	mapRecords["AACT"] = Tes4RecordIgnore::create;
	mapRecords["GLOB"] = Tes4RecordIgnore::create;
	mapRecords["CLAS"] = Tes4RecordIgnore::create;
	mapRecords["FACT"] = Tes4RecordIgnore::create;
	mapRecords["HDPT"] = Tes4RecordIgnore::create;
	mapRecords["EYES"] = Tes4RecordIgnore::create;
	mapRecords["RACE"] = Tes4RecordIgnore::create;
	mapRecords["SOUN"] = Tes4RecordIgnore::create;
	mapRecords["ASPC"] = Tes4RecordIgnore::create;
	mapRecords["MGEF"] = Tes4RecordIgnore::create;
	mapRecords["ENCH"] = Tes4RecordIgnore::create;
	mapRecords["SPEL"] = Tes4RecordIgnore::create;
	mapRecords["SCRL"] = Tes4RecordIgnore::create;
	mapRecords["ACTI"] = Tes4RecordIgnore::create;
	mapRecords["TACT"] = Tes4RecordIgnore::create;
	mapRecords["ARMO"] = Tes4RecordIgnore::create;
	mapRecords["BOOK"] = Tes4RecordIgnore::create;
	mapRecords["CONT"] = Tes4RecordIgnore::create;
	mapRecords["DOOR"] = Tes4RecordIgnore::create;
	mapRecords["INGR"] = Tes4RecordIgnore::create;
	mapRecords["LIGH"] = Tes4RecordIgnore::create;
	mapRecords["MISC"] = Tes4RecordIgnore::create;
	mapRecords["APPA"] = Tes4RecordIgnore::create;
	mapRecords["STAT"] = Tes4RecordIgnore::create;
	mapRecords["MSTT"] = Tes4RecordIgnore::create;
	mapRecords["GRAS"] = Tes4RecordIgnore::create;
	mapRecords["TREE"] = Tes4RecordIgnore::create;
	mapRecords["FLOR"] = Tes4RecordIgnore::create;
	mapRecords["FURN"] = Tes4RecordIgnore::create;
	mapRecords["WEAP"] = Tes4RecordIgnore::create;
	mapRecords["AMMO"] = Tes4RecordIgnore::create;
	mapRecords["LVLN"] = Tes4RecordIgnore::create;
	mapRecords["KEYM"] = Tes4RecordIgnore::create;
	mapRecords["ALCH"] = Tes4RecordIgnore::create;
	mapRecords["IDLM"] = Tes4RecordIgnore::create;
	mapRecords["COBJ"] = Tes4RecordIgnore::create;
	mapRecords["PROJ"] = Tes4RecordIgnore::create;
	mapRecords["HAZD"] = Tes4RecordIgnore::create;
	mapRecords["SLGM"] = Tes4RecordIgnore::create;
	mapRecords["LVLI"] = Tes4RecordIgnore::create;
	mapRecords["WTHR"] = Tes4RecordIgnore::create;
	mapRecords["CLMT"] = Tes4RecordIgnore::create;
	mapRecords["SPGD"] = Tes4RecordIgnore::create;
	mapRecords["RFCT"] = Tes4RecordIgnore::create;
	mapRecords["REGN"] = Tes4RecordIgnore::create;
	mapRecords["NAVI"] = Tes4RecordIgnore::create;
	mapRecords["REFR"] = Tes4RecordIgnore::create;
	mapRecords["ACHR"] = Tes4RecordIgnore::create;
	mapRecords["NAVM"] = Tes4RecordIgnore::create;
	mapRecords["NPC_"] = Tes4RecordIgnore::create;
	mapRecords["PGRE"] = Tes4RecordIgnore::create;
	mapRecords["PHZD"] = Tes4RecordIgnore::create;
	mapRecords["DIAL"] = Tes4RecordIgnore::create;
	mapRecords["INFO"] = Tes4RecordIgnore::create;
	mapRecords["QUST"] = Tes4RecordIgnore::create;
	mapRecords["IDLE"] = Tes4RecordIgnore::create;
	mapRecords["PACK"] = Tes4RecordIgnore::create;
	mapRecords["CSTY"] = Tes4RecordIgnore::create;
	mapRecords["LSCR"] = Tes4RecordIgnore::create;
	mapRecords["LVSP"] = Tes4RecordIgnore::create;
	mapRecords["ANIO"] = Tes4RecordIgnore::create;
	mapRecords["WATR"] = Tes4RecordIgnore::create;
	mapRecords["EFSH"] = Tes4RecordIgnore::create;
	mapRecords["EXPL"] = Tes4RecordIgnore::create;
	mapRecords["DEBR"] = Tes4RecordIgnore::create;
	mapRecords["IMGS"] = Tes4RecordIgnore::create;
	mapRecords["IMAD"] = Tes4RecordIgnore::create;
	mapRecords["FLST"] = Tes4RecordIgnore::create;
	mapRecords["PERK"] = Tes4RecordIgnore::create;
	mapRecords["BPTD"] = Tes4RecordIgnore::create;
	mapRecords["ADDN"] = Tes4RecordIgnore::create;
	mapRecords["AVIF"] = Tes4RecordIgnore::create;
	mapRecords["CAMS"] = Tes4RecordIgnore::create;
	mapRecords["CPTH"] = Tes4RecordIgnore::create;
	mapRecords["VTYP"] = Tes4RecordIgnore::create;
	mapRecords["MATT"] = Tes4RecordIgnore::create;
	mapRecords["IPCT"] = Tes4RecordIgnore::create;
	mapRecords["IPDS"] = Tes4RecordIgnore::create;
	mapRecords["ARMA"] = Tes4RecordIgnore::create;
	mapRecords["ECZN"] = Tes4RecordIgnore::create;
	mapRecords["LCTN"] = Tes4RecordIgnore::create;
	mapRecords["MESG"] = Tes4RecordIgnore::create;
	mapRecords["DOBJ"] = Tes4RecordIgnore::create;
	mapRecords["LGTM"] = Tes4RecordIgnore::create;
	mapRecords["MUSC"] = Tes4RecordIgnore::create;
	mapRecords["FSTP"] = Tes4RecordIgnore::create;
	mapRecords["FSTS"] = Tes4RecordIgnore::create;
	mapRecords["SMBN"] = Tes4RecordIgnore::create;
	mapRecords["SMQN"] = Tes4RecordIgnore::create;
	mapRecords["SMEN"] = Tes4RecordIgnore::create;
	mapRecords["DLBR"] = Tes4RecordIgnore::create;
	mapRecords["MUST"] = Tes4RecordIgnore::create;
	mapRecords["DLVW"] = Tes4RecordIgnore::create;
	mapRecords["WOOP"] = Tes4RecordIgnore::create;
	mapRecords["SHOU"] = Tes4RecordIgnore::create;
	mapRecords["EQUP"] = Tes4RecordIgnore::create;
	mapRecords["RELA"] = Tes4RecordIgnore::create;
	mapRecords["SCEN"] = Tes4RecordIgnore::create;
	mapRecords["ASTP"] = Tes4RecordIgnore::create;
	mapRecords["OTFT"] = Tes4RecordIgnore::create;
	mapRecords["ARTO"] = Tes4RecordIgnore::create;
	mapRecords["MATO"] = Tes4RecordIgnore::create;
	mapRecords["MOVT"] = Tes4RecordIgnore::create;
	mapRecords["SNDR"] = Tes4RecordIgnore::create;
	mapRecords["DUAL"] = Tes4RecordIgnore::create;
	mapRecords["SNCT"] = Tes4RecordIgnore::create;
	mapRecords["SOPM"] = Tes4RecordIgnore::create;
	mapRecords["COLL"] = Tes4RecordIgnore::create;
	mapRecords["CLFM"] = Tes4RecordIgnore::create;
	mapRecords["REVB"] = Tes4RecordIgnore::create;
}

//-----------------------------------------------------------------------------
void Tes4RecordIgnore::writeFile(FILE* pFile)
{
}