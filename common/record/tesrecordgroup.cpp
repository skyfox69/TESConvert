#include "common/record/tesrecordgroup.h"

//-----------------------------------------------------------------------------
TesRecordGroup::TesRecordGroup(TesFileType const fileType)
	:	TesRecordBase(TesRecordType::RECORDGROUP, fileType),
		_labelL(0),
		_groupType(0),
		_timestamp(0),
		_version(0)
{}

//-----------------------------------------------------------------------------
TesRecordGroup::~TesRecordGroup()
{}

//-----------------------------------------------------------------------------
size_t TesRecordGroup::sizeRecord()
{
	return _size;
}

//-----------------------------------------------------------------------------
size_t TesRecordGroup::sizeTotal()
{
	return _size;
}

//-----------------------------------------------------------------------------
void TesRecordGroup::dump(const short depth)
{}