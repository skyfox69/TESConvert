#include "tes4/record/tes4recordgeneric.h"
#include "common/util/compressor.h"
#include "common/util/tesoptions.h"
#include <cstring>

//-----------------------------------------------------------------------------
Tes4RecordGeneric::Tes4RecordGeneric(unsigned char* pBuffer)
	:	TesRecordMain(TesFileType::TES4),
		_pDataBuffer (nullptr)
{
	if (pBuffer != nullptr) {
		toString4(_name,     pBuffer);
		toSizeT  (_size,     &pBuffer[4]);
		toULong  (_flags,    &pBuffer[8]);
		toULong  (_id,       &pBuffer[12]);
		toULong  (_revision, &pBuffer[16]);
		toUShort (_version,  &pBuffer[20]);
		toUShort (_unknownS, &pBuffer[22]);
	}
}

//-----------------------------------------------------------------------------
Tes4RecordGeneric::Tes4RecordGeneric(const string name, const unsigned long id)
	:	TesRecordMain(TesFileType::TES4),
		_pDataBuffer (nullptr)
{
	_name = name;
	_id   = id;
}

//-----------------------------------------------------------------------------
Tes4RecordGeneric::~Tes4RecordGeneric()
{
	if (_pDataBuffer != nullptr)		delete[] _pDataBuffer;
	_pDataBuffer = nullptr;
}

//-----------------------------------------------------------------------------
size_t Tes4RecordGeneric::sizeRecord()
{
	return 24;
}

//-----------------------------------------------------------------------------
size_t Tes4RecordGeneric::sizeTotal()
{
	return _size + sizeRecord();
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4RecordGeneric::create(unsigned char* pBuffer)
{
	return new Tes4RecordGeneric(pBuffer);
}

//-----------------------------------------------------------------------------
void Tes4RecordGeneric::registerClass(map<string, TesCreateFunction>& mapRecords)
{
	mapRecords["TES4"] = Tes4RecordGeneric::create;
	mapRecords["WRLD"] = Tes4RecordGeneric::create;
	mapRecords["CELL"] = Tes4RecordGeneric::create;
	mapRecords["LAND"] = Tes4RecordGeneric::create;
	mapRecords["TXST"] = Tes4RecordGeneric::create;
	mapRecords["LTEX"] = Tes4RecordGeneric::create;
}

//-----------------------------------------------------------------------------
void Tes4RecordGeneric::writeFile(FILE* pFile)
{
	writeString4(_name,     pFile);
	writeSizeT  (_size,     pFile);
	writeULong  (_flags,    pFile);
	writeULong  (_id,       pFile);
	writeULong  (_revision, pFile);
	writeUShort (_version,  pFile);
	writeUShort (_unknownS, pFile);

	if (_pDataBuffer != nullptr) {
		fwrite(_pDataBuffer, 1, _size * sizeof(unsigned char), pFile);
	} else {
		for (auto& pRecord : *this) {
			pRecord->writeFile(pFile);
		}
	}
}

//-----------------------------------------------------------------------------
size_t Tes4RecordGeneric::calcSizes()
{
	if (TESOptions::getInstance()->_doCompress && (_name == "LAND")) {
		unsigned char*	pBufferSrc(nullptr);
		unsigned char*	pStart    (nullptr);

		//  determine original size
		_size = 0;
		for (auto& pRecord : *this) {
			_size += pRecord->calcSizes();
		}

		//  compress buffers
		pBufferSrc   = new unsigned char[_size];
		_pDataBuffer = new unsigned char[_size+4];
		pStart       = pBufferSrc;

		memset(pBufferSrc,   0, _size * sizeof(unsigned char));
		memset(_pDataBuffer, 0xff, (_size+4) * sizeof(unsigned char));
		writeSizeT(_size, _pDataBuffer);

		//  fill source buffer
		for (auto& pRecord : *this) {
			pStart = pRecord->writeMem(pStart);
		}

		//  compress
		int	compressed = Compressor::deflateBuffer(pBufferSrc, _size, _pDataBuffer+4, _size);

		if (compressed > 0) {
			_size   = compressed + 4;
			_flags |= 0x00040000;
		} else {
			delete _pDataBuffer;
			_pDataBuffer = nullptr;
		}

		//  clean up
		delete[] pBufferSrc;

	} else {
		return TesRecordMain::calcSizes();
	}

	return sizeTotal();
}