#include "tes4/subrecord/tes4subrecordatxt.h"

//-----------------------------------------------------------------------------
Tes4SubRecordATXT::Tes4SubRecordATXT(unsigned char quadrant, unsigned long textureId, unsigned short layer)
	:	TesRecordSub(TesFileType::TES4),
		_textureId  (textureId),
		_layer      (layer),
		_quadrant   (quadrant),
		_unknown    (0)
{
	_name = "ATXT";
	_size = 8;
}

//-----------------------------------------------------------------------------
Tes4SubRecordATXT::Tes4SubRecordATXT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,      pBuffer);
		toUShort4(_size,      &pBuffer[4]);
		toULong  (_textureId, &pBuffer[6]);
		toChar   (_quadrant,  &pBuffer[10]);
		toChar   (_unknown,   &pBuffer[11]);
		toUShort (_layer,     &pBuffer[12]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordATXT::~Tes4SubRecordATXT()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordATXT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  quadrant:: %d\n", indent.c_str(), _quadrant);
	printf("%s  layer::    %d\n", indent.c_str(), _layer);
	printf("%s  formId::   %d / 0x%08X\n", indent.c_str(), _textureId, _textureId);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordATXT::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes quadrant=\"%d\" layer=\"%d\" formId=\"%d / 0x%08X\"", _quadrant, _layer, _textureId, _textureId);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordATXT::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordATXT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordATXT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDATXT"] = Tes4SubRecordATXT::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordATXT::writeFile(FILE* pFile)
{
	writeString4(_name,      pFile);
	writeUShort4(_size,      pFile);
	writeULong  (_textureId, pFile);
	writeChar   (_quadrant,  pFile);
	writeChar   (_unknown,   pFile);
	writeUShort (_layer,     pFile);
}

//-----------------------------------------------------------------------------
unsigned char* Tes4SubRecordATXT::writeMem(unsigned char* pMemory)
{
	pMemory += writeString4(_name,      pMemory);
	pMemory += writeUShort4(_size,      pMemory);
	pMemory += writeULong  (_textureId, pMemory);
	*pMemory++ = _quadrant;
	*pMemory++ = _unknown;
	pMemory += writeUShort(_layer, pMemory);
	return pMemory;
}