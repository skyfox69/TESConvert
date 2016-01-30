#include "tes3/record/tes3recordgeneric.h"

//-----------------------------------------------------------------------------
Tes3RecordGeneric::Tes3RecordGeneric(unsigned char* pBuffer)
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
Tes3RecordGeneric::~Tes3RecordGeneric()
{}

//-----------------------------------------------------------------------------
size_t Tes3RecordGeneric::sizeRecord()
{
	return 16;
}

//-----------------------------------------------------------------------------
size_t Tes3RecordGeneric::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3RecordGeneric::create(unsigned char* pBuffer)
{
	return new Tes3RecordGeneric(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3RecordGeneric::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES3"] = Tes3RecordGeneric::create;
	mapRecords["GMST"] = Tes3RecordGeneric::create;
	mapRecords["GLOB"] = Tes3RecordGeneric::create;
	mapRecords["REGN"] = Tes3RecordGeneric::create;
	mapRecords["LTEX"] = Tes3RecordGeneric::create;
	mapRecords["CELL"] = Tes3RecordGeneric::create;
	mapRecords["LAND"] = Tes3RecordGeneric::create;
}

//-----------------------------------------------------------------------------
void Tes3RecordGeneric::writeFile(FILE* pFile)
{}
