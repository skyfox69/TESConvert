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
	mapRecords["REFRVMAD"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXPRM"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXTEL"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXNDP"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXRMR"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXPPA"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRPDTO"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRINAM"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXLOC"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXESP"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXLIG"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXRGD"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXLKR"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRONAM"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXTNM"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXAPR"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXSPC"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXCNT"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXIS2"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXMBP"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXRGB"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXWCU"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRSCHR"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXMRK"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRFULL"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXRNK"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXLTW"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXOCP"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXLCN"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRSCTX"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXCZC"] = Tes4SubRecordIgnore::create;
	mapRecords["REFRXCZA"] = Tes4SubRecordIgnore::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordIgnore::writeFile(FILE* pFile)
{
}