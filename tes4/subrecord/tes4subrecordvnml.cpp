#include "tes4/subrecord/tes4subrecordvnml.h"

//-----------------------------------------------------------------------------
Tes4SubRecordVNML::Tes4SubRecordVNML(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		pBuffer += 6;
		for (short i(0); i < 33; ++i) {
			for (short j(0); j < 33; ++j, pBuffer += 3) {
				_buffer[j][i]._xr = pBuffer[0];
				_buffer[j][i]._yg = pBuffer[1];
				_buffer[j][i]._zb = pBuffer[2];
			}
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordVNML::~Tes4SubRecordVNML()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
/**
	for (short i(0); i < 33; ++i) {
		printf("%s  ", indent.c_str());
		for (short j(0); j < 33; ++j) {
			printf("(%02X%02X%02X),", _buffer[i][j]._xr, _buffer[i][j]._yg, _buffer[i][j]._zb);
		}
		printf("\n");
	}
/**/
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordVNML::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordVNML(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordVNML::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["LANDVNML"] = Tes4SubRecordVNML::create;
	mapRecords["LANDVCLR"] = Tes4SubRecordVNML::create;
}
