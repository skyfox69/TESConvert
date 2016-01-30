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

	if (_flags &= 0x00040000) {
		printf("----------------------------------\n%s%s [%dp|%d]\n", indent.c_str(), _name.c_str(), sizeTotal(), sizeRecord());
	} else {
		printf("----------------------------------\n%s%s [%d|%d]\n", indent.c_str(), _name.c_str(), sizeTotal(), sizeRecord());
	}
	printf("%s  flags:: 0x%08X\n", indent.c_str(), _flags);
	if (_id != 0) {
		printf("%s  id::    %d\n", indent.c_str(), _id);
	}
	for_each(begin(),
			 end(),
			 [depth](TesRecordBase* pRecord) {
				 pRecord->dump(depth+2);
				 return true;
			 }
			);
}

//-----------------------------------------------------------------------------
void TesRecordMain::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes sizeTotal=\"%d\" sizeRecord=\"%d\" flags=\"0x%08X\"", sizeTotal(), sizeRecord(), _flags);
	if (_id != 0) {
		printf(" id=\"%d\"", _id);
	}
	printf("/>\n");
	for_each(begin(),
			 end(),
			 [](TesRecordBase* pRecord) {
				 pRecord->dumpXml();
				 return true;
			 }
			);
	printf("</%s>\n", _name.c_str());
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

//-----------------------------------------------------------------------------
bool TesRecordMain::compressed()
{
	return (_flags & 0x00040000) != 0;
}

//-----------------------------------------------------------------------------
size_t TesRecordMain::calcSizes()
{
	_size = 0;
	for (auto& pRecord : *this) {
		_size += pRecord->calcSizes();
	}

	return sizeTotal();
}