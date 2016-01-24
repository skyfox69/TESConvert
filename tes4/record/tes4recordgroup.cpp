#include "tes4/record/tes4recordgroup.h"
#include <algorithm>

static string	groupNames[] = {"Top", "World Children", "Interior Cell Block", "Interior Cell Sub-Block",
								"Exterior Cell Block", "Exterior Cell Sub-Block", "Cell Children",
								"Topic Children", "Cell Persistent Children", "Cell Temporary Children",
								"Cell Visible Distant Children" };

//-----------------------------------------------------------------------------
Tes4RecordGroup::Tes4RecordGroup(unsigned char* pBuffer)
	:	TesRecordGroup(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,      pBuffer);
		toSizeT  (_size,      &pBuffer[4]);
		toULong  (_labelL,    &pBuffer[8]);
		toString4(_labelS,    &pBuffer[8]);
		toULong  (_groupType, &pBuffer[12]);
		toUShort (_timestamp, &pBuffer[16]);
		toUShort (_unknown1,  &pBuffer[18]);
		toUShort (_version,   &pBuffer[20]);
		toUShort (_unknown2,  &pBuffer[22]);
	}
}

//-----------------------------------------------------------------------------
Tes4RecordGroup::~Tes4RecordGroup()
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
size_t Tes4RecordGroup::sizeRecord()
{
	return 24;
}

//-----------------------------------------------------------------------------
size_t Tes4RecordGroup::sizeTotal()
{
	return _size;
}

//-----------------------------------------------------------------------------
void Tes4RecordGroup::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("  --------------------------------\n%s%s [%d|%d]\n", indent.c_str(), _name.c_str(), sizeTotal(), sizeRecord());
	printf("%s  groupSize:: %d\n", indent.c_str(), _size);
	switch (_groupType) {
		case 0:
			printf("%s  label::    %s\n", indent.c_str(), _labelS.c_str());
			break;
		case 2:
		case 3:
			printf("%s  number::   %d\n", indent.c_str(), _labelL);
			break;
		case 4:
		case 5:
			printf("%s  x::        %d\n", indent.c_str(), (_labelL & 0x0000FFFF));
			printf("%s  y::        %d\n", indent.c_str(), (_labelL >> 32));
			break;
		default:
			printf("%s  formid::   %d\n", indent.c_str(), _labelL);
	}
	printf("%s  groupType:: 0x%08X [%s]\n", indent.c_str(), _groupType, groupNames[_groupType].c_str());
	printf("%s  timestamp:: %02d.%02d\n", indent.c_str(), (_timestamp & 0x00ff), (_timestamp >> 8));
	printf("%s  version::   %d\n", indent.c_str(), _version);
	for_each(begin(),
			 end(),
			 [depth](TesRecordBase* pRecord) {
				 pRecord->dump(depth+2);
				 return true;
			 }
			);
}

//-----------------------------------------------------------------------------
void Tes4RecordGroup::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes sizeTotal=\"%d\" sizeRecord=\"%d\" groupSize=\"0x%08X\"", sizeTotal(), sizeRecord(), _size);
	switch (_groupType) {
		case 0:
			printf(" label=\"%s\"", _labelS.c_str());
			break;
		case 2:
		case 3:
			printf(" number=\"%d\"", _labelL);
			break;
		case 4:
		case 5:
			printf(" x=\"%d\"", (_labelL & 0x0000FFFF));
			printf(" y=\"%d\"", (_labelL >> 32));
			break;
		default:
			printf(" formid=\"%d\"", _labelL);
	}
	printf(" groupType=\"0x%08X [%s]\"", _groupType, groupNames[_groupType].c_str());
	printf(" timestamp=\"%02d.%02d\"", (_timestamp & 0x00ff), (_timestamp >> 8));
	printf(" version=\"%d\"", _version);
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
TesRecordBase* Tes4RecordGroup::create(unsigned char* pBuffer)
{
	return new Tes4RecordGroup(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4RecordGroup::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["GRUP"] = Tes4RecordGroup::create;
}
