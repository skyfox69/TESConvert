#include "tes3/subrecord/tes3subrecordsinglefloat.h"

//-----------------------------------------------------------------------------
Tes3SubRecordSingleFloat::Tes3SubRecordSingleFloat(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toFloat4 (_value, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordSingleFloat::~Tes3SubRecordSingleFloat()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleFloat::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %f\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordSingleFloat::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordSingleFloat(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordSingleFloat::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["GMSTFLTV"] = Tes3SubRecordSingleFloat::create;
	mapRecords["GLOBFLTV"] = Tes3SubRecordSingleFloat::create;
	mapRecords["FRMRXSCL"] = Tes3SubRecordSingleFloat::create;
	mapRecords["FRMRFLTV"] = Tes3SubRecordSingleFloat::create;
	mapRecords["CELLWHGT"] = Tes3SubRecordSingleFloat::create;
}