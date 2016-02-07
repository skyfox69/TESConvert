#ifndef TESRECORDBASE_H
#define	TESRECORDBASE_H

#include <stdlib.h>
#include <cstdint>
#include <string>
#include "common/types/tesfiletype.h"
#include "common/types/tesrecordtype.h"

using namespace std;

//-----------------------------------------------------------------------------
class TesRecordBase
{
	public:
		TesRecordType						_recordType;
		TesFileType							_fileType;
		string								_name;
		size_t								_size;
		
											TesRecordBase(TesRecordType const recordType=TesRecordType::NOTSET,
														  TesFileType const fileType = TesFileType::UNKNOWN);
		virtual								~TesRecordBase();
		virtual	TesRecordType				recordType();
		virtual	TesFileType					fileType();
		virtual	size_t						sizeRecord() = 0;
		virtual	size_t						sizeTotal() = 0;
		virtual	void						dump(const short depth) = 0;
		virtual	void						dumpXml() = 0;
		virtual	TesRecordBase*				findSubRecord(string const token) = 0;
		virtual	bool						compressed();
		virtual	size_t						calcSizes() = 0;
		virtual	void						writeFile(FILE* pFile) = 0;
		virtual	unsigned char*				writeMem(unsigned char* pMemory);
};

#endif	/* TESRECORDBASE_H */