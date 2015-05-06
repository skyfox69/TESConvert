#include "tes4/record/tes4recordgeneric.h"

//-----------------------------------------------------------------------------
Tes4RecordGeneric::Tes4RecordGeneric(unsigned char* pBuffer)
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
Tes4RecordGeneric::~Tes4RecordGeneric()
{}

//-----------------------------------------------------------------------------
size_t Tes4RecordGeneric::sizeRecord()
{
	return 24;
}

//-----------------------------------------------------------------------------
size_t Tes4RecordGeneric::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4RecordGeneric::create(unsigned char* pBuffer)
{
	return new Tes4RecordGeneric(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4RecordGeneric::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4"] = Tes4RecordGeneric::create;
	mapRecords["WRLD"] = Tes4RecordGeneric::create;
	mapRecords["CELL"] = Tes4RecordGeneric::create;
	mapRecords["LAND"] = Tes4RecordGeneric::create;
}
