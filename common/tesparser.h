#ifndef	TESPARSER_H
#define	TESPARSER_H

#include "common/util/endian.h"
#include "common/util/verbosity.h"
#include "common/types/tesfiletype.h"
#include <vector>

class TesRecordBase;
class ITesRecordFactory;

//-----------------------------------------------------------------------------
class TesParser : public Endian, protected Verbosity, public vector<TesRecordBase*>
{
	enum class TesParserBreakReason : std::int8_t { ALL_OK = 0, UNKNOWN_RECORD = 1, WAS_DUMPED = 2};

	private:
		ITesRecordFactory*					_pFactory;
		unsigned char*						_pFileBuffer;
		unsigned char*						_pFileBufferEnd;
		string								_message;
		TesFileType							_fileType;
		unsigned char						_dumpCompressed;

		virtual	bool						readFile(string const fileName);
		virtual	unsigned char*				parsePartial(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent, TesParserBreakReason& breakReason);
		virtual	unsigned char*				parseCompressed(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent, TesParserBreakReason& breakReason);
		
	public:
											TesParser();
		virtual								~TesParser();
		
		virtual	bool						parse(string const fileName);
		virtual	TesFileType					fileType() { return _fileType; }
};
#endif  /* TESPARSER_H */
