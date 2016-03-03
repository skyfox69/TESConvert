#include "tes4/subrecord/tes4subrecordstatmnam.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4SubRecordSTATMNAM::Tes4SubRecordSTATMNAM()
	:	TesRecordSub(TesFileType::TES4)
{
	_name = "MNAM";
	_size = 1040;
}

//-----------------------------------------------------------------------------
Tes4SubRecordSTATMNAM::Tes4SubRecordSTATMNAM(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		unsigned char	buffer[1050] = {0};

		toString4(_name,    pBuffer);
		toUShort4(_size,    &pBuffer[4]);
		memcpy(buffer, &pBuffer[6], 1040);
		_modelLOD[0] = (char*) &(buffer[0]);
		_modelLOD[1] = (char*) &(buffer[260]);
		_modelLOD[2] = (char*) &(buffer[520]);
		_modelLOD[3] = (char*) &(buffer[780]);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSTATMNAM::~Tes4SubRecordSTATMNAM()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSTATMNAM::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	for (short i(0); i < 4; ++i) {
		printf("%s  log[%d]:: %s\n", indent.c_str(), i, _modelLOD[i].c_str());
	}
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSTATMNAM::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes");
	for (short i(0); i < 4; ++i) {
		printf(" modelLOD[%d]=\"%s\"", i, _modelLOD[i].c_str());
	}
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSTATMNAM::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSTATMNAM(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSTATMNAM::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["STATMNAM"] = Tes4SubRecordSTATMNAM::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSTATMNAM::writeFile(FILE* pFile)
{
	writeString4(_name,    pFile);
	writeUShort4(_size,    pFile);


	
}
