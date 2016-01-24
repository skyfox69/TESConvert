#include "tes4/subrecord/tes4subrecordxclccell.h"

//-----------------------------------------------------------------------------
Tes4SubRecordXCLCCELL::Tes4SubRecordXCLCCELL(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name,  pBuffer);
		toUShort4(_size,  &pBuffer[4]);
		toLong   (_x,     &pBuffer[6]);
		toLong   (_y,     &pBuffer[10]);
		if (_size > 8) {
			toULong(_flags, &pBuffer[14]);
		}
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordXCLCCELL::~Tes4SubRecordXCLCCELL()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordXCLCCELL::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  x::     %d\n", indent.c_str(), _x);
	printf("%s  y::     %d\n", indent.c_str(), _y);
	if (_size > 8) {
		printf("%s  flags:: 0x%08X\n", indent.c_str(), _flags);
	}
}

//-----------------------------------------------------------------------------
void Tes4SubRecordXCLCCELL::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes x=\"%d\" y=\"%d\"", _x, _y);
	if (_size > 8) {
		printf(" flags=\"0x%08X\"", _flags);
	}
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordXCLCCELL::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordXCLCCELL(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordXCLCCELL::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["CELLXCLC"] = Tes4SubRecordXCLCCELL::create;
}
