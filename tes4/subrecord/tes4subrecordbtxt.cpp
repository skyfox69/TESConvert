#include "tes4/subrecord/tes4subrecordbtxt.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordBTXT::Tes4SubRecordBTXT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,      pBuffer);
		toUShort4(_size,      &pBuffer[4]);
		toULong  (_textureId, &pBuffer[6]);
		toChar   (_quadrant,  &pBuffer[10]);
		memcpy(_unknown, &(pBuffer[11]), 3*sizeof(unsigned char));
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordBTXT::~Tes4SubRecordBTXT()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordBTXT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  quadrant:: %d\n", indent.c_str(), _quadrant);
	printf("%s  formId::   %d / 0x%08X\n", indent.c_str(), _textureId, _textureId);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordBTXT::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordBTXT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordBTXT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDBTXT"] = Tes4SubRecordBTXT::create;
}