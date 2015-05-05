#include "tes3/subrecord/tes3subrecordintvland.h"

//-----------------------------------------------------------------------------
Tes3SubRecordINTVLAND::Tes3SubRecordINTVLAND(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toLong   (_cellX, &pBuffer[8]);
		toLong   (_cellY, &pBuffer[12]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordINTVLAND::~Tes3SubRecordINTVLAND()
{}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordINTVLAND::sizeRecord()
{
	return 8;
}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordINTVLAND::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3SubRecordINTVLAND::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  cellX:: %d\n", indent.c_str(), _cellX);
	printf("%s  cellY:: %d\n", indent.c_str(), _cellY);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordINTVLAND::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordINTVLAND(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordINTVLAND::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDINTV"] = Tes3SubRecordINTVLAND::create;
	mapRecords["CELLCNDT"] = Tes3SubRecordINTVLAND::create;
	mapRecords["FRMRCNDT"] = Tes3SubRecordINTVLAND::create;
}