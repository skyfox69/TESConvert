#include "common/record/tesrecordbase.h"

//-----------------------------------------------------------------------------
TesRecordBase::TesRecordBase(TesRecordType const recordType, TesFileType const fileType)
	:	_recordType(recordType),
		_fileType  (fileType),
		_size      (0)
{}

//-----------------------------------------------------------------------------
TesRecordBase::~TesRecordBase()
{}

//-----------------------------------------------------------------------------
TesRecordType TesRecordBase::recordType()
{
	return _recordType;
}

//-----------------------------------------------------------------------------
TesFileType TesRecordBase::fileType()
{
	return _fileType;
}

//-----------------------------------------------------------------------------
bool TesRecordBase::compressed()
{
	return false;
}