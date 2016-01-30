#include "common/tesparser.h"
#include "common/types/tesrecordtype.h"
#include "common/record/tesrecordmain.h"
#include "common/record/tesrecordgroup.h"
#include "tes3/tes3recordfactory.h"
#include "tes4/tes4recordfactory.h"
#include "util/tesoptions.h"
#include "tes4/subrecord/tes4subrecordsinglestring.h"
#include <algorithm>
#include <zlib.h>
#include <cstring>

using namespace std;

//-----------------------------------------------------------------------------
TesParser::TesParser()
	:	Verbosity(),
		_pFactory      (nullptr),
		_pFileBuffer   (nullptr),
		_pFileBufferEnd(nullptr),
		_fileType      (TesFileType::UNKNOWN)
{
	_dumpCompressed = TESOptions::getInstance()->_dumpCompressed;
}

//-----------------------------------------------------------------------------
TesParser::~TesParser()
{
	//  clean up
	if (_pFileBuffer != nullptr)	delete[] _pFileBuffer;
	if (_pFactory    != nullptr)	delete _pFactory;

	remove_if(begin(),
			  end(),
			  [](TesRecordBase* pRecord) {
				  delete pRecord;
				  return true;
			  }
			 );
}

//-----------------------------------------------------------------------------
bool TesParser::readFile(string const fileName)
{
	//  clean up
	if (_pFileBuffer != nullptr) {
		delete[] _pFileBuffer;
		_pFileBuffer = nullptr;
	}

	//  read new file
	FILE*	pFile   (fopen(fileName.c_str(), "rb"));
	long	fileSize(0);
	
	if (pFile == NULL)		return false;
	
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	rewind(pFile);
	
	_pFileBuffer = new unsigned char[fileSize];
	fread(_pFileBuffer, sizeof(unsigned char), fileSize, pFile);
	fclose(pFile);
	_pFileBufferEnd = _pFileBuffer + fileSize;

	return true;
}

//-----------------------------------------------------------------------------
bool TesParser::parse(string const fileName)
{
	bool	retVal(false);

	//  read file
	verbose0("reading file '%s'", fileName.c_str());
	readFile(fileName);
	
	//  parse file
	if (_pFileBuffer != nullptr) {
		TesParserBreakReason	breakReason(TesParserBreakReason::ALL_OK);
		string					token;

		if (_pFactory != nullptr) {
			delete _pFactory;
			_pFactory = nullptr;
		}
		
		toString4(token, _pFileBuffer);
		if (token == "TES3") {
			_fileType = TesFileType::TES3;
			_pFactory = new Tes3RecordFactory();
			verbose0("  found TES3 header => assuming \x1B[32mMorrowind\033[0m file");
		}
		else if (token == "TES4") {
			_fileType = TesFileType::TES4;
			_pFactory = new Tes4RecordFactory();
			verbose0("  found TES4 header => assuming \x1B[32mSkyrim\033[0m file");
		}
		else {
			verbose0("  \x1B[31munknown header type => skipping file\033[0m");
			return false;
		}
		
		//  parse buffer
		verbose0("begin parsing");
		retVal = (parsePartial(_pFileBuffer, _pFileBufferEnd, this, nullptr, breakReason) != nullptr);
		verbose0("\nend parsing");

	}  //  if (_pFileBuffer != nullptr)

	if (!_message.empty()) {
		verbose0("%s", _message.c_str());
	}

	return retVal;
}

//-----------------------------------------------------------------------------
unsigned char* TesParser::parsePartial(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent, TesParserBreakReason& breakReason)
{
	TesRecordBase*	pRecordNew(nullptr);
	unsigned char*	pStart    (pBlockStart);
	string			tokenAct;
	string			token;
	static int		recIndex(0);

	if (pParent != nullptr) {
		tokenAct = pParent->_name;
	}

	while (pStart < pBlockEnd) {
		toString4(token, pStart);

		if ((token == "FRMR") && (tokenAct == "FRMR")) {
			return pStart;
		}

		//  get Record
		pRecordNew = _pFactory->create(token, tokenAct, pStart);

		if (pRecordNew == nullptr) {
			_message = "\x1B[31munknown record \x1B[1;31m" + token + "\033[0m";
			breakReason = TesParserBreakReason::UNKNOWN_RECORD;
			return nullptr;
		}

		switch (pRecordNew->recordType()) {
			case TesRecordType::RECORDGROUP: {
				unsigned char* pStartGrp(pStart);

				verbose2("found \x1B[33m%s\033[0m [GROUP]", token.c_str());
				if (pRecordNew->_fileType == TesFileType::TES3) {
					pRecordNew->_size = pBlockEnd - pStart;
				}

				pStart = parsePartial(pStart + pRecordNew->sizeRecord(),
									  pStart + pRecordNew->sizeTotal(),
									  (TesRecordGroup*) pRecordNew,
									  pRecordNew, breakReason);

				if (pCollection != nullptr) {
					pCollection->push_back(pRecordNew);
				}

				if (pStart == nullptr) {
					if (breakReason == TesParserBreakReason::UNKNOWN_RECORD) {
						breakReason = TesParserBreakReason::WAS_DUMPED;
						pRecordNew->dump(0);
					}
					return nullptr;
				}
				continue;
			}
				
			case TesRecordType::RECORD: {
				verbose2("found \x1B[33m%s\033[0m [RECORD]", token.c_str());
				if (pRecordNew->compressed()) {
					if (parseCompressed(pStart + pRecordNew->sizeRecord(),
										pStart + pRecordNew->sizeTotal(),
										(TesRecordMain*) pRecordNew,
										pRecordNew,
										breakReason) == nullptr) {
						if (pCollection != nullptr) {
							pCollection->push_back(pRecordNew);
						}
						if (breakReason == TesParserBreakReason::UNKNOWN_RECORD) {
							breakReason = TesParserBreakReason::WAS_DUMPED;
							pRecordNew->dump(0);
						}
						return nullptr;
					}
				} else {
					if (parsePartial(pStart + pRecordNew->sizeRecord(),
									 pStart + pRecordNew->sizeTotal(),
									 (TesRecordMain*) pRecordNew,
									 pRecordNew,
									 breakReason) == nullptr) {
						if (pCollection != nullptr) {
							pCollection->push_back(pRecordNew);
						}
						if (breakReason == TesParserBreakReason::UNKNOWN_RECORD) {
							breakReason = TesParserBreakReason::WAS_DUMPED;
							pRecordNew->dump(0);
						}
						return nullptr;
					}
				}
				break;
			}
				
			case TesRecordType::SUBRECORD:
				verbose2("found \x1B[33m%s\033[0m [SUBRECORD]", token.c_str());
				break;
				
			default:
				_message = "\x1B[31munknown record \x1B[1;31m" + token + "\033[0m";
				breakReason = TesParserBreakReason::UNKNOWN_RECORD;
				return nullptr;
		}
		
		if (pCollection != nullptr) {
			pCollection->push_back(pRecordNew);
		}
		
		pStart += pRecordNew->sizeTotal();

		if ((pParent != nullptr) && ((++recIndex%1000) == 0)) {
			fprintf(stderr, ".");
		}
		
	}  //  while (pStart < pBlockEnd)
	
	return pStart;
}

//-----------------------------------------------------------------------------
unsigned char* TesParser::parseCompressed(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent, TesParserBreakReason& breakReason)
{
	size_t	sizeComp  (pParent->_size - 4);
	size_t	sizeDecomp(0);

	//  early return for ignored records
	if (pBlockStart >= pBlockEnd) {
		return pBlockStart;
	}

	toSizeT(sizeDecomp, pBlockStart);
	pBlockStart += 4;

	unsigned char*		pBufIntern(new unsigned char[sizeDecomp]);
	unsigned char*		pBufEnd   (pBufIntern + sizeDecomp);
	unsigned char*		pStart    (pBufIntern);

	inflateBuffer(pBlockStart, sizeComp, pBufIntern, sizeDecomp);

	if (_dumpCompressed > 0) {
		char	fileName[100] = {0};

		if (_dumpCompressed == 2 ) {
			sprintf(fileName, "./block_last.bin");
		} else {
			sprintf(fileName, "./block_at_0x%08x.bin", pBlockStart);
		}
		
		FILE*	pFile(fopen(fileName, "wb"));

		if (pFile != NULL) {
			fwrite(pBufIntern, sizeDecomp, 1, pFile);
			fflush(pFile);
			fclose(pFile);
		}
	}  //  if (_dumpCompressed)

	if (parsePartial(pBufIntern,
					 pBufEnd,
					 (TesRecordMain*) pParent,
					 pParent,
					 breakReason) == nullptr) {
		return nullptr;
	}

	delete[] pBufIntern;

	return pBlockEnd;
}

//-----------------------------------------------------------------------------
int TesParser::inflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst)
{
	z_stream	strm = {0};
	int			retCode(-1);
	
	strm.total_in  = lenSrc;
	strm.avail_in  = lenSrc;
	strm.total_out = lenDst;
	strm.avail_out = lenDst;
	strm.next_in   = (Bytef*) pBufSrc;
	strm.next_out  = (Bytef*) pBufDst;
	strm.zalloc    = Z_NULL;
	strm.zfree     = Z_NULL;
	strm.opaque    = Z_NULL;

	retCode = inflateInit2(&strm, (15 + 32));
	if (retCode == Z_OK) {
		retCode = inflate(&strm, Z_FINISH);
		if (retCode == Z_STREAM_END) {
			retCode = strm.total_out;
		}
	}

	inflateEnd(&strm);

	return retCode;
}

