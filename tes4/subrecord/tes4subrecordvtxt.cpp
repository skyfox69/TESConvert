#include "tes4/subrecord/tes4subrecordvtxt.h"

static	size_t	szEntryVTXT = sizeof(Tes4SubRecordVTXT::EntryVTXT);

//-----------------------------------------------------------------------------
Tes4SubRecordVTXT::Tes4SubRecordVTXT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4),
		_pEntries   (nullptr),
		_count      (0)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toUShort4(_size,     &pBuffer[4]);

		_count    = _size / szEntryVTXT;
		_pEntries = new EntryVTXT[_count];
		pBuffer  += 6;

		for (size_t idx(0); idx < _count; ++idx, pBuffer += szEntryVTXT) {
			toUShort (_pEntries[idx]._position, pBuffer);
			toChar   (_pEntries[idx]._unknown1, &pBuffer[2]);
			toChar   (_pEntries[idx]._unknown2, &pBuffer[3]);
			toFloat4 (_pEntries[idx]._opacity,  &pBuffer[4]);
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordVTXT::~Tes4SubRecordVTXT()
{
	if (_pEntries != nullptr)		delete[] _pEntries;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVTXT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	for (size_t idx(0); idx < _count; ++idx) {
		printf("%s  position:: %d\toapcity::  %f\n", indent.c_str(), _pEntries[idx]._position, _pEntries[idx]._opacity);
	}
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVTXT::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes count=\"%d\"", _count);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordVTXT::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordVTXT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVTXT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVTXT"] = Tes4SubRecordVTXT::create;
}