#include "tes3/subrecord/tes3subrecordvtex.h"
#include <cstring>

static int	quads[4][3] = {{0, 0, 0}, {8, 0, 64} , {0, 8, 256} , {8, 8, 320}};

//-----------------------------------------------------------------------------
Tes3SubRecordVTEX::Tes3SubRecordVTEX(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,   pBuffer);
		toSizeT  (_size,   &pBuffer[4]);
		memcpy(_texIds, &(pBuffer[8]), 16*16*sizeof(unsigned short));
		
		//  standardize texture map
		unsigned char*		pOrig ((unsigned char*) &_texIds[0][0]);
		int					quadX (0);
		int					quadY (0);
		int					offset(0);
		
		for (int quad(0); quad < 4; ++quad) {
			quadX  = quads[quad][0];
			quadY  = quads[quad][1];
			offset = quads[quad][2];

			for (int i(0); i < 2; ++i) {
				offset += (i*64);
				for (int j(0); j < 2; ++j) {
					for (int k(0); k < 4; ++k) {
						memcpy(&_texStd[quadY+k+(4*i)][quadX+(4*j)], pOrig + offset, 8);
						offset += 8;
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordVTEX::~Tes3SubRecordVTEX()
{}

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
void Tes3SubRecordVTEX::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("</%s>\n", _name.c_str());
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

//-----------------------------------------------------------------------------
void Tes3SubRecordVTEX::writeFile(FILE* pFile)
{}