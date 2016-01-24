#include "tes3/record/tes3recordgroup.h"
#include <algorithm>

//-----------------------------------------------------------------------------
Tes3RecordGroup::Tes3RecordGroup(unsigned char* pBuffer)
	:	TesRecordGroup(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toSizeT  (_size,     &pBuffer[4]);
		toULong  (_objIndex, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes3RecordGroup::~Tes3RecordGroup()
{}

//-----------------------------------------------------------------------------
size_t Tes3RecordGroup::sizeRecord()
{
	return 12;
}

//-----------------------------------------------------------------------------
size_t Tes3RecordGroup::sizeTotal()
{
	return _size;
}

//-----------------------------------------------------------------------------
void Tes3RecordGroup::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("  --------------------------------\n%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %d\n", indent.c_str(), _objIndex);
	for_each(begin(),
			 end(),
			 [depth](TesRecordBase* pRecord) {
				 pRecord->dump(depth+2);
				 return true;
			 }
			);
}

//-----------------------------------------------------------------------------
void Tes3RecordGroup::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes objIndex=\"%d\"", _objIndex);
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
TesRecordBase* Tes3RecordGroup::create(unsigned char* pBuffer)
{
	return new Tes3RecordGroup(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3RecordGroup::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLFRMR"] = Tes3RecordGroup::create;
}
