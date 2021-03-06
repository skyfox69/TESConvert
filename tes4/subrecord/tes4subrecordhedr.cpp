#include "tes4/subrecord/tes4subrecordhedr.h"

//-----------------------------------------------------------------------------
Tes4SubRecordHEDR::Tes4SubRecordHEDR()
	:	TesRecordSub (TesFileType::TES4),
		_version     (0.94),
		_numRecords  (0),
		_nextObjectId(0)
{
	_name = "HEDR";
	_size = 12;
}

//-----------------------------------------------------------------------------
Tes4SubRecordHEDR::Tes4SubRecordHEDR(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,         pBuffer);
		toUShort4(_size,         &pBuffer[4]);
		toFloat4 (_version,      &pBuffer[6]);
		toULong  (_numRecords,   &pBuffer[10]);
		toULong  (_nextObjectId, &pBuffer[14]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordHEDR::~Tes4SubRecordHEDR()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  version::      %.2f\n", indent.c_str(), _version);
	printf("%s  numRecords::   %d\n", indent.c_str(), _numRecords);
	printf("%s  nextObjectId:: %d - 0x%08X\n", indent.c_str(), _nextObjectId, _nextObjectId);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes version=\".2f\" numRecords=\"%d\" nextObjectId=\"%d\"", _version, _numRecords, _nextObjectId);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordHEDR::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordHEDR(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4HEDR"] = Tes4SubRecordHEDR::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordHEDR::writeFile(FILE* pFile)
{
	writeString4(_name,         pFile);
	writeUShort4(_size,         pFile);
	writeFloat4 (_version,      pFile);
	writeULong  (_numRecords,   pFile);
	writeULong  (_nextObjectId, pFile);
}