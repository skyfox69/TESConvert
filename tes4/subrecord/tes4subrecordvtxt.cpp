#include "tes4/subrecord/tes4subrecordvtxt.h"
#include <cstring>

static	size_t	szEntryVTXT = sizeof(Tes4SubRecordVTXT::EntryVTXT);

//-----------------------------------------------------------------------------
Tes4SubRecordVTXT::Tes4SubRecordVTXT(float opacity, vector<unsigned short>& points)
	:	TesRecordSub(TesFileType::TES4),
		_pEntries   (nullptr),
		_count      (0)
{
	_name     = "VTXT";
	_count    = 0;
	_size     = points.size() * szEntryVTXT;
	_pEntries = new EntryVTXT[points.size()];

	for (auto& point : points) {
		_pEntries[_count]._opacity  = opacity;
		_pEntries[_count]._position = point;
		_pEntries[_count]._unknown1 = 0;
		_pEntries[_count]._unknown2 = 0;
		++_count;
	}
}

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

//-----------------------------------------------------------------------------
void Tes4SubRecordVTXT::writeFile(FILE* pFile)
{
	writeString4(_name, pFile);
	writeUShort4(_size, pFile);
	for (unsigned short idx(0); idx < _count; ++idx) {
		writeUShort(_pEntries[idx]._position, pFile);
		writeChar  (_pEntries[idx]._unknown1, pFile);
		writeChar  (_pEntries[idx]._unknown2, pFile);
		writeFloat4(_pEntries[idx]._opacity,  pFile);
	}
}

//-----------------------------------------------------------------------------
unsigned char* Tes4SubRecordVTXT::writeMem(unsigned char* pMemory)
{
	pMemory += writeString4(_name, pMemory);
	pMemory += writeUShort4(_size, pMemory);
	for (unsigned short idx(0); idx < _count; ++idx) {
		pMemory += writeUShort(_pEntries[idx]._position, pMemory);
		*pMemory++ = _pEntries[idx]._unknown1;
		*pMemory++ = _pEntries[idx]._unknown2;
		pMemory += writeFloat4(_pEntries[idx]._opacity,  pMemory);
	}
	return pMemory;
}