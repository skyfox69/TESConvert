#include "tes3/subrecord/tes3subrecordwnam.h"

//-----------------------------------------------------------------------------
Tes3SubRecordWNAM::Tes3SubRecordWNAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toSizeT  (_size,   &pBuffer[4]);
		pBuffer += 8;
		for (short i(0); i < 9; ++i) {
			for (short j(0); j < 9; ++j, ++pBuffer) {
				_data[j][i] = pBuffer[0];
			}
		}
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordWNAM::~Tes3SubRecordWNAM()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordWNAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	for (short i(0); i < 9; ++i) {
		printf("%s  ", indent.c_str());
		for (short j(0); j < 9; ++j) {
			printf("%02X,", _data[i][j]);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------
void Tes3SubRecordWNAM::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordWNAM::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordWNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordWNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDWNAM"] = Tes3SubRecordWNAM::create;
}
