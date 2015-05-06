#ifndef	TESPARSER_H
#define	TESPARSER_H

#include "common/util/endian.h"
#include "common/types/tesfiletype.h"
#include <vector>

class TesRecordBase;
class ITesRecordFactory;

//-----------------------------------------------------------------------------
class TesParser : public Endian, public vector<TesRecordBase*>
{
	private:
		ITesRecordFactory*					_pFactory;
		unsigned char*						_pFileBuffer;
		unsigned char*						_pFileBufferEnd;
		string								_message;
		TesFileType							_fileType;
		bool								_verbose;

		virtual	bool						readFile(string const fileName);
		virtual	unsigned char*				parsePartial(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent);
		virtual	unsigned char*				parseCompressed(unsigned char* pBlockStart, unsigned char* pBlockEnd, vector<TesRecordBase*>* pCollection, TesRecordBase* pParent);
		virtual	int							inflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst);
		
	public:
											TesParser();
		virtual								~TesParser();
		
		virtual	bool						parse(string const fileName);
		virtual	TesFileType					fileType() { return _fileType; }
};
#endif  /* TESPARSER_H */
