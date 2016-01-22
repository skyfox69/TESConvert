#include "tes4/subrecord/tes4subrecorddodt.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordDODT::Tes4SubRecordDODT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,           pBuffer);
		toUShort4(_size,           &pBuffer[4]);
		toFloat4 (_widthMin,       &pBuffer[6]);
		toFloat4 (_widthMax,       &pBuffer[10]);
		toFloat4 (_heightMin,      &pBuffer[14]);
		toFloat4 (_heightMax,      &pBuffer[18]);
		toFloat4 (_depth,          &pBuffer[22]);
		toFloat4 (_shininess,      &pBuffer[26]);
		toFloat4 (_parallaxScale,  &pBuffer[30]);
		toChar   (_parallaxPasses, &pBuffer[34]);
		toChar   (_flags,          &pBuffer[35]);
		memcpy(_unknown, &(pBuffer[36]), 2*sizeof(unsigned char));
		toULong  (_rgb,            &pBuffer[38]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordDODT::~Tes4SubRecordDODT()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordDODT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  widthMin::        %f\n", indent.c_str(), _widthMin);
	printf("%s  widthMax::        %f\n", indent.c_str(), _widthMax);
	printf("%s  heihgtMin::       %f\n", indent.c_str(), _heightMin);
	printf("%s  heihgtMax::       %f\n", indent.c_str(), _heightMax);
	printf("%s  depth::           %f\n", indent.c_str(), _depth);
	printf("%s  shininess::       %f\n", indent.c_str(), _shininess);
	printf("%s  parallaxScale::   %f\n", indent.c_str(), _parallaxScale);
	printf("%s  parallaxPasses::  %0x02d\n", indent.c_str(), _parallaxPasses);
	printf("%s  flags::           %0x02d\n", indent.c_str(), _flags);
	printf("%s  rgb::\n", indent.c_str());
	printf("%s    red::   0x%02X\n", indent.c_str(), ((_rgb)       & 0x000000FF));
	printf("%s    green:: 0x%02X\n", indent.c_str(), ((_rgb >>  8) & 0x000000FF));
	printf("%s    blue::  0x%02X\n", indent.c_str(), ((_rgb >> 16) & 0x000000FF));
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordDODT::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordDODT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordDODT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TXSTDODT"] = Tes4SubRecordDODT::create;
}
