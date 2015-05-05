#include "tes3/subrecord/tes3subrecorddatacell.h"

//-----------------------------------------------------------------------------
Tes3SubRecordDATACELL::Tes3SubRecordDATACELL(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toULong  (_flags, &pBuffer[8]);
		toLong   (_gridX, &pBuffer[12]);
		toLong   (_gridY, &pBuffer[16]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordDATACELL::~Tes3SubRecordDATACELL()
{}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordDATACELL::sizeRecord()
{
	return 8;
}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordDATACELL::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  flags:: 0x%08X\n", indent.c_str(), _flags);
	printf("%s  gridX:: %d\n", indent.c_str(), _gridX);
	printf("%s  gridY:: %d\n", indent.c_str(), _gridY);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordDATACELL::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordDATACELL(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLDATA"] = Tes3SubRecordDATACELL::create;
}