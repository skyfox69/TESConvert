#include "tes3/subrecord/tes3subrecordambi.h"

//-----------------------------------------------------------------------------
Tes3SubRecordAMBI::Tes3SubRecordAMBI(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,       pBuffer);
		toSizeT  (_size,       &pBuffer[4]);
		toULong  (_ambient,    &pBuffer[8]);
		toULong  (_sunlight,   &pBuffer[12]);
		toULong  (_fog,        &pBuffer[16]);
		toFloat4 (_fogDensity, &pBuffer[20]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordAMBI::~Tes3SubRecordAMBI()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordAMBI::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  ambient::    0x%02X, 0x%02X, 0x%02X\n", indent.c_str(), (_ambient & 0x000000FF), ((_ambient >>  8) & 0x000000FF), ((_ambient >>  8) & 0x000000FF));
	printf("%s  sunlight::   0x%02X, 0x%02X, 0x%02X\n", indent.c_str(), (_sunlight & 0x000000FF), ((_sunlight >>  8) & 0x000000FF), ((_sunlight >>  8) & 0x000000FF));
	printf("%s  fog::        0x%02X, 0x%02X, 0x%02X\n", indent.c_str(), (_fog & 0x000000FF), ((_fog >>  8) & 0x000000FF), ((_fog >>  8) & 0x000000FF));
	printf("%s  fogDensity:: %f\n", indent.c_str(), _fogDensity);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordAMBI::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" ambient=\"0x%02X, 0x%02X, 0x%02X\"", (_ambient & 0x000000FF), ((_ambient >>  8) & 0x000000FF), ((_ambient >>  8) & 0x000000FF));
	printf(" sunlight=\"0x%02X, 0x%02X, 0x%02X\"", (_sunlight & 0x000000FF), ((_sunlight >>  8) & 0x000000FF), ((_sunlight >>  8) & 0x000000FF));
	printf(" fog=\"0x%02X, 0x%02X, 0x%02X\"", (_fog & 0x000000FF), ((_fog >>  8) & 0x000000FF), ((_fog >>  8) & 0x000000FF));
	printf(" fogDensity=\"%f\"", _fogDensity);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordAMBI::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordAMBI(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordAMBI::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLAMBI"] = Tes3SubRecordAMBI::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordAMBI::writeFile(FILE* pFile)
{}
