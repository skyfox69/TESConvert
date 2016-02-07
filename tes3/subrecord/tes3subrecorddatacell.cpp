#include "tes3/subrecord/tes3subrecorddatacell.h"

//-----------------------------------------------------------------------------
Tes3SubRecordDATACELL::Tes3SubRecordDATACELL(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toULong  (_flags, &pBuffer[8]);
		toLong   (_gridX, &pBuffer[12]);
		toLong   (_gridY, &pBuffer[16]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordDATACELL::~Tes3SubRecordDATACELL()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  flags:: 0x%08X\n", indent.c_str(), _flags);
	printf("%s  gridX:: %d\n", indent.c_str(), _gridX);
	printf("%s  gridY:: %d\n", indent.c_str(), _gridY);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" flags=\"0x%08X\"", _flags);
	printf(" gridX=\"%d\"", _gridX);
	printf(" gridY=\"%d\"", _gridY);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordDATACELL::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordDATACELL(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLDATA"] = Tes3SubRecordDATACELL::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATACELL::writeFile(FILE* pFile)
{}
