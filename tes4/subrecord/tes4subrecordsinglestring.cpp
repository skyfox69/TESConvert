#include "tes4/subrecord/tes4subrecordsinglestring.h"

//-----------------------------------------------------------------------------
Tes4SubRecordSingleString::Tes4SubRecordSingleString(unsigned char* pBuffer)
	:	TesRecordSub(TesFileType::TES4)
{
	if (pBuffer != nullptr) {
		toString4(_name, pBuffer);
		toUShort4(_size, &pBuffer[4]);
		toStringN(_text, &pBuffer[6], _size);
	}
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleString::Tes4SubRecordSingleString(string const name, string const text)
	:	TesRecordSub(TesFileType::TES4),
		_text(text)
{
	_name = name;
	_size = _text.size() + 1;
}

//-----------------------------------------------------------------------------
Tes4SubRecordSingleString::~Tes4SubRecordSingleString()
{}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::dump(const short depth)
{
	string		indent(depth, ' ');
	
	printf("%s%s\n", indent.c_str(), _name.c_str());
	printf("%s  %s\n", indent.c_str(), _text.c_str());
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::dumpXml()
{
	printf("<%s>", _name.c_str());
	printf("<attributes text=\"%s\"", _text.c_str());
	printf("/>\n");
	printf("</%s>\n", _name.c_str());
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4SubRecordSingleString::create(unsigned char* pBuffer)
{
	return new Tes4SubRecordSingleString(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4CNAM"] = Tes4SubRecordSingleString::create;
	mapRecords["TES4MAST"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDTNAM"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDUNAM"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX00"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX01"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX02"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX03"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX04"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX05"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX06"] = Tes4SubRecordSingleString::create;
	mapRecords["TXSTTX07"] = Tes4SubRecordSingleString::create;
	mapRecords["LTEXEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["MATTEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["MATTMNAM"] = Tes4SubRecordSingleString::create;
	mapRecords["CELLEDID"] = Tes4SubRecordSingleString::create;
	mapRecords["CELLXWEM"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDMODL"] = Tes4SubRecordSingleString::create;
	mapRecords["WRLDXWEM"] = Tes4SubRecordSingleString::create;
}

//-----------------------------------------------------------------------------
void Tes4SubRecordSingleString::writeFile(FILE* pFile)
{
	writeString4(_name, pFile);
	writeUShort4(_size, pFile);
	writeStringN(_text, pFile);
}