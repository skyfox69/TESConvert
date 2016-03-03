#include "tes4/subrecord/tes4subrecordignore.h"

//-----------------------------------------------------------------------------
Tes4SubRecordIgnore::Tes4SubRecordIgnore(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toUShort4(_size, &pBuffer[4]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordIgnore::~Tes4SubRecordIgnore()
{}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordIgnore::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordIgnore(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordIgnore::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLXCLL"] = Tes4SubRecordIgnore::create;
	mapRecords["CELLTVDT"] = Tes4SubRecordIgnore::create;
	mapRecords["CELLMHDT"] = Tes4SubRecordIgnore::create;
	mapRecords["CELLXCLR"] = Tes4SubRecordIgnore::create;
	mapRecords["CELLXWCU"] = Tes4SubRecordIgnore::create;
	mapRecords["WRLDRNAM"] = Tes4SubRecordIgnore::create;
	mapRecords["WRLDOFST"] = Tes4SubRecordIgnore::create;
	mapRecords["WRLDMHDT"] = Tes4SubRecordIgnore::create;
	mapRecords["TES4ONAM"] = Tes4SubRecordIgnore::create;
	mapRecords["STATMODT"] = Tes4SubRecordIgnore::create;
	mapRecords["STATMODS"] = Tes4SubRecordIgnore::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordIgnore::writeFile(FILE* pFile)
{
}