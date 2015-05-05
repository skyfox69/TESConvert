#include "common/record/tesrecordmain.h"
#include <algorithm>

//-----------------------------------------------------------------------------
TesRecordMain::TesRecordMain(TesFileType const fileType)
	:	TesRecordBase(TesRecordType::RECORD, fileType),
		_flags       (0),
		_id          (0),
		_revision    (0),
		_unknownL    (0),
		_version     (0),
		_unknownS    (0)
{}

//-----------------------------------------------------------------------------
TesRecordMain::~TesRecordMain()
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
size_t TesRecordMain::sizeRecord()
{
	return _size;
}

//-----------------------------------------------------------------------------
size_t TesRecordMain::sizeTotal()
{
	return _size;
}

//-----------------------------------------------------------------------------
void TesRecordMain::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("----------------------------------\n%s%s\n", indent.c_str(), _name.c_str());
	for_each(begin(),
			 end(),
			 [depth](TesRecordBase* pRecord) {
				 pRecord->dump(depth+2);
				 return true;
			 }
			);
}

//-----------------------------------------------------------------------------
TesRecordBase* TesRecordMain::findSubRecord(const string token)
{
	auto pSubRecord = find_if(begin(),
							  end(),
							  [token](TesRecordBase* pRecord) {
								return (pRecord->_name == token);
							}
						   );
	return (pSubRecord != end()) ? *pSubRecord : nullptr;

}