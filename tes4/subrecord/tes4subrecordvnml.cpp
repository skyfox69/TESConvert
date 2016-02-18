#include "tes4/subrecord/tes4subrecordvnml.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordVNML::Tes4SubRecordVNML(unsigned char type)
	:	TesRecordSub(TesFileType::TES4)
{
	_name = (type == 0) ? "VCLR" : "VNML";
	_size = 3267;
	memset(_buffer, 0, 33*33*3*sizeof(unsigned char));
}

//-----------------------------------------------------------------------------
Tes4SubRecordVNML::Tes4SubRecordVNML(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		memcpy(_buffer, &(pBuffer[6]), 33*33*3*sizeof(unsigned char));
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordVNML::~Tes4SubRecordVNML()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
/**
	for (short i(0); i < 33; ++i) {
		printf("%s  ", indent.c_str());
		for (short j(0); j < 33; ++j) {
			printf("(%02X%02X%02X),", _buffer[i][j]._xr, _buffer[i][j]._yg, _buffer[i][j]._zb);
		}
		printf("\n");
	}
/**/
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordVNML::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordVNML(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVNML"] = Tes4SubRecordVNML::create;
	mapRecords["LANDVCLR"] = Tes4SubRecordVNML::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::writeFile(FILE* pFile)
{
	writeString4(_name,  pFile);
	writeUShort4(_size,  pFile);
	fwrite(_buffer, 1, 33*33*3, pFile);
}

//-----------------------------------------------------------------------------
unsigned char* Tes4SubRecordVNML::writeMem(unsigned char* pMemory)
{
	pMemory += writeString4(_name,   pMemory);
	pMemory += writeUShort4(_size,   pMemory);
	memcpy(pMemory, _buffer, 33*33*3*sizeof(unsigned char));
	return (pMemory + 33*33*3);
}