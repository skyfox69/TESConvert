#include "common/record/tesrecordsub.h"

//-----------------------------------------------------------------------------
TesRecordSub::TesRecordSub(TesFileType const fileType)
	:	TesRecordBase(TesRecordType::SUBRECORD, fileType)
{}

//-----------------------------------------------------------------------------
TesRecordSub::~TesRecordSub()
{}

//-----------------------------------------------------------------------------
size_t TesRecordSub::sizeRecord()
{
	return (_fileType == TesFileType::TES4) ? 6 : 8;
}

//-----------------------------------------------------------------------------
size_t TesRecordSub::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void TesRecordSub::dump(const short depth)
{}

//-----------------------------------------------------------------------------
void TesRecordSub::dumpXml()
{}

//-----------------------------------------------------------------------------
size_t TesRecordSub::calcSizes()
{
	return sizeTotal();
}