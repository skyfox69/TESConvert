#include "tes3/subrecord/tes3subrecorddatates3.h"

//-----------------------------------------------------------------------------
Tes3SubRecordDATATES3::Tes3SubRecordDATATES3(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES3)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toSizeT  (_size,  &pBuffer[4]);
		toLong8  (_value, &pBuffer[8]);
	}
}

//-----------------------------------------------------------------------------
Tes3SubRecordDATATES3::~Tes3SubRecordDATATES3()
{}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %d\n", indent.c_str(), _value);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	printf(" value=\"%d\"", _value);
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3SubRecordDATATES3::create(unsigned char* pBuffer)
{
	return new Tes3SubRecordDATATES3(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES3DATA"] = Tes3SubRecordDATATES3::create;
}

//-----------------------------------------------------------------------------
void Tes3SubRecordDATATES3::writeFile(FILE* pFile)
{}