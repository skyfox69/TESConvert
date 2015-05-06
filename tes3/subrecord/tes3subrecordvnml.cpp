#include "tes3/subrecord/tes3subrecordvnml.h"

//-----------------------------------------------------------------------------
Tes3SubRecordVNML::Tes3SubRecordVNML(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		pBuffer += 8;
		for (short i(0); i < 65; ++i) {
			for (short j(0); j < 65; ++j, pBuffer += 3) {
				_buffer[j][i]._xr = pBuffer[0];
				_buffer[j][i]._yg = pBuffer[1];
				_buffer[j][i]._zb = pBuffer[2];
			}
		}
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordVNML::~Tes3SubRecordVNML()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordVNML::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	for (short i(0); i < 65; ++i) {
		printf("%s  ", indent.c_str());
		for (short j(0); j < 65; ++j) {
			printf("(%02X%02X%02X),", _buffer[i][j]._xr, _buffer[i][j]._yg, _buffer[i][j]._zb);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordVNML::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordVNML(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordVNML::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVNML"] = Tes3SubRecordVNML::create;
	mapRecords["LANDVCLR"] = Tes3SubRecordVNML::create;
}
