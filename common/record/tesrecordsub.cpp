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
	return _size;
}

//-----------------------------------------------------------------------------
size_t TesRecordSub::sizeTotal()
{
	return _size;
}

//-----------------------------------------------------------------------------
void TesRecordSub::dump(const short depth)
{}