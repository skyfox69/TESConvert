#include "common/record/tesrecordgroup.h"
#include <algorithm>

//-----------------------------------------------------------------------------
TesRecordGroup::TesRecordGroup(TesFileType const fileType)
	:	TesRecordBase(TesRecordType::RECORDGROUP, fileType),
		_labelL      (0),
		_groupType   (0),
		_timestamp   (0),
		_version     (0),
		_unknown1    (0),
		_unknown2    (0)
{}

//-----------------------------------------------------------------------------
TesRecordGroup::~TesRecordGroup()
{
	remove_if(begin(),
			  end(),
			  [](TesRecordBase* pRecord) {
				  delete pRecord;
				  return true;
			  }
			 );
}

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

//-----------------------------------------------------------------------------
void TesRecordGroup::dumpXml()
{
	printf("<TesRecordGroup></TesRecordGroup>\n");
}

//-----------------------------------------------------------------------------
size_t TesRecordGroup::calcSizes()
{
	_size = sizeRecord();
	for (auto& pRecord : *this) {
		_size += pRecord->calcSizes();
	}

	return sizeTotal();
}