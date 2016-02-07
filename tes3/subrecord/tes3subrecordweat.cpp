#include "tes3/subrecord/tes3subrecordweat.h"

//-----------------------------------------------------------------------------
Tes3SubRecordWEAT::Tes3SubRecordWEAT(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toSizeT  (_size,     &pBuffer[4]);
		toChar   (_clear,    &pBuffer[8]);
		toChar   (_cloudy,   &pBuffer[9]);
		toChar   (_foggy,    &pBuffer[10]);
		toChar   (_overcast, &pBuffer[11]);
		toChar   (_rain,     &pBuffer[12]);
		toChar   (_thunder,  &pBuffer[13]);
		toChar   (_ash,      &pBuffer[14]);
		toChar   (_blight,   &pBuffer[15]);	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordWEAT::~Tes3SubRecordWEAT()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordWEAT::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  clear::    %d\n", indent.c_str(), _clear);
	printf("%s  cloudy::   %d\n", indent.c_str(), _cloudy);
	printf("%s  foggy::    %d\n", indent.c_str(), _foggy);
	printf("%s  overcast:: %d\n", indent.c_str(), _overcast);
	printf("%s  rain::     %d\n", indent.c_str(), _rain);
	printf("%s  thunder::  %d\n", indent.c_str(), _thunder);
	printf("%s  ash::      %d\n", indent.c_str(), _ash);
	printf("%s  blight::   %d\n", indent.c_str(), _blight);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordWEAT::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" clear=\"%d\"", _clear);
	printf(" cloudy=\"%d\"", _cloudy);
	printf(" foggy=\"%d\"", _foggy);
	printf(" overcast=\"%d\"", _overcast);
	printf(" rain=\"%d\"", _rain);
	printf(" thunder=\"%d\"", _thunder);
	printf(" ash=\"%d\"", _ash);
	printf(" blight=\"%d\"", _blight);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordWEAT::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordWEAT(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordWEAT::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["REGNWEAT"] = Tes3SubRecordWEAT::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordWEAT::writeFile(FILE* pFile)
{}