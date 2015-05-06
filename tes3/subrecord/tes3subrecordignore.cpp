#include "tes3/subrecord/tes3subrecordignore.h"

//-----------------------------------------------------------------------------
Tes3SubRecordIgnore::Tes3SubRecordIgnore(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordIgnore::~Tes3SubRecordIgnore()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordIgnore::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s\x1B[1;35mTemp. ignored:: %s\033[0m\n", indent.c_str(), _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordIgnore::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordIgnore(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordIgnore::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["FRMRUNAM"] = Tes3SubRecordIgnore::create;
}