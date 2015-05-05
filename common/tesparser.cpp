#include "common/tesparser.h"
#include "common/types/tesrecordtype.h"
#include "common/record/tesrecordmain.h"
#include "common/record/tesrecordgroup.h"
#include "tes3/tes3recordfactory.h"
#include "util/tesoptions.h"
#include <algorithm>

using namespace std;

//-----------------------------------------------------------------------------
TesParser::TesParser()
	:	_pFactory      (nullptr),
		_pFileBuffer   (nullptr),
		_pFileBufferEnd(nullptr),
		_fileType      (TesFileType::UNKNOWN)
{
	_verbose = TESOptions::getInstance()->_verbose;
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
	printf("reading file '%s'\n", fileName.c_str());
	readFile(fileName);
	
	//  parse file
	if (_pFileBuffer != nullptr) {
		string		token;

		if (_pFactory != nullptr) {
			delete _pFactory;
			_pFactory = nullptr;
		}
		
		toString4(token, _pFileBuffer);
		if (token == "TES3") {
			_fileType = TesFileType::TES3;
			_pFactory = new Tes3RecordFactory();
			printf("  found TES3 header => assuming \x1B[32mMorrowind\033[0m file\n");
		}
		else if (token == "TES4") {
			_fileType = TesFileType::TES4;
			printf("  found TES4 header => assuming \x1B[32mSkyrim\033[0m file\n");
		}
		else {
			printf("  \x1B[31munknown header type => skipping file\033[0m\n");
			return false;
		}
		
		//  parse buffer
		printf("begin parsing\n");
		retVal = (parsePartial(_pFileBuffer, _pFileBufferEnd, this, nullptr) != nullptr);
		printf("\nend parsing\n");

	}  //  if (_pFileBuffer != nullptr)
	
	if (!_message.empty()) {
		printf("%s\n", _message.c_str());
	}
	
	return retVal;
}

//-----------------------------------------------------------------------------
unsigned char* TesParser::parsePartial(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent)
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
			return nullptr;
		}

		switch (pRecordNew->recordType()) {
			case TesRecordType::RECORDGROUP:
				if (_verbose)	printf("found \x1B[33m%s\033[0m [GROUP]\n", token.c_str());
				if (pRecordNew->_fileType == TesFileType::TES3) {
					pRecordNew->_size = pBlockEnd - pStart;
				}

				pStart = parsePartial(pStart + pRecordNew->sizeRecord(),
									  pStart + pRecordNew->sizeTotal(),
									  (TesRecordGroup*) pRecordNew, pRecordNew);

				if (pCollection != nullptr) {
					pCollection->push_back(pRecordNew);
				}

				if (pStart == nullptr) {
					pRecordNew->dump(0);
					return nullptr;
				}
				continue;
				break;
				
			case TesRecordType::RECORD:
				if (_verbose)	printf("found \x1B[33m%s\033[0m [RECORD]\n", token.c_str());
				if (parsePartial(pStart + pRecordNew->sizeRecord(),
								 pStart + pRecordNew->sizeTotal(),
								 (TesRecordMain*) pRecordNew, pRecordNew) == nullptr) {
					if (pCollection != nullptr) {
						pCollection->push_back(pRecordNew);
					}
					pRecordNew->dump(0);
					return nullptr;
				}
				break;
				
			case TesRecordType::SUBRECORD:
				if (_verbose)	printf("found \x1B[33m%s\033[0m [SUBRECORD]\n", token.c_str());
				break;
				
			default:
				_message = "\x1B[31munknown record \x1B[1;31m" + token + "\033[0m";
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
