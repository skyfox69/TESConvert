#include "tes3/subrecord/tes3subrecordsnam.h"

//-----------------------------------------------------------------------------
Tes3SubRecordSNAM::Tes3SubRecordSNAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toSizeT  (_size,   &pBuffer[4]);
		toStringN(_text,   &pBuffer[8], 32);
		toChar   (_chance, &pBuffer[41]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordSNAM::~Tes3SubRecordSNAM()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordSNAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  name::   %s\n", indent.c_str(), _text.c_str());
	printf("%s  chance:: 0x%02X\n", indent.c_str(), _chance);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordSNAM::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordSNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["REGNSNAM"] = Tes3SubRecordSNAM::create;
}
