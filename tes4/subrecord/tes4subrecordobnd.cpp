#include "tes4/subrecord/tes4subrecordobnd.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordOBND::Tes4SubRecordOBND(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toUShort4(_size,   &pBuffer[4]);
		memcpy(_unknown, &(pBuffer[6]), 12*sizeof(unsigned char));
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordOBND::~Tes4SubRecordOBND()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordOBND::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordOBND(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordOBND::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TXSTOBND"] = Tes4SubRecordOBND::create;
}
