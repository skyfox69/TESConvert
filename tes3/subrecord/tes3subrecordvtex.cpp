#include "tes3/subrecord/tes3subrecordvtex.h"

//-----------------------------------------------------------------------------
Tes3SubRecordVTEX::Tes3SubRecordVTEX(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toSizeT  (_size,   &pBuffer[4]);
		pBuffer += 8;
		for (short i(0); i < 16; ++i) {
			for (short j(0); j < 16; ++j, pBuffer += 2) {
				toUShort(_texIds[i][j] ,pBuffer);
			}
		}
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordVTEX::~Tes3SubRecordVTEX()
{}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordVTEX::sizeRecord()
{
	return 8;
}

//-----------------------------------------------------------------------------
size_t Tes3SubRecordVTEX::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVTEX::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	for (short i(0); i < 16; ++i) {
		printf("%s  ", indent.c_str());
		for (short j(0); j < 16; ++j) {
			printf("%02X,", _texIds[i][j]);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordVTEX::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordVTEX(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVTEX::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVTEX"] = Tes3SubRecordVTEX::create;
}
