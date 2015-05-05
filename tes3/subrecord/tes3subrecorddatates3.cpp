#include "tes3/subrecord/tes3subrecorddatates3.h"

//-----------------------------------------------------------------------------
Tes3SubRecordDATATES3::Tes3SubRecordDATATES3(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toLong8  (_value, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordDATATES3::~Tes3SubRecordDATATES3()
{}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordDATATES3::sizeRecord()
{
	return 8;
}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordDATATES3::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %d\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordDATATES3::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordDATATES3(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES3DATA"] = Tes3SubRecordDATATES3::create;
}