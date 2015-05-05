#include "tes3/subrecord/tes3subrecordflags.h"

//-----------------------------------------------------------------------------
Tes3SubRecordFlags::Tes3SubRecordFlags(unsigned char* pBuffer)
	:	Tes3SubRecordSingleULong(pBuffer)
{}

//-----------------------------------------------------------------------------
Tes3SubRecordFlags::~Tes3SubRecordFlags()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordFlags::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  0x%08X\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordFlags::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordFlags(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordFlags::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["FRMRNAM9"] = Tes3SubRecordFlags::create;
	mapRecords["FRMRXCHG"] = Tes3SubRecordFlags::create;
	mapRecords["FRMRDELE"] = Tes3SubRecordFlags::create;
	mapRecords["FRMRMVRF"] = Tes3SubRecordFlags::create;
	mapRecords["CELLMVRF"] = Tes3SubRecordFlags::create;
}