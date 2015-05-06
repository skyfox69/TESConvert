#ifndef TESRECORDMAIN_H
#define	TESRECORDMAIN_H

#include "common/record/tesrecordbase.h"
#include "common/util/endian.h"
#include <vector>

//-----------------------------------------------------------------------------
class TesRecordMain : public TesRecordBase, public Endian, public vector<TesRecordBase*>
{
	public:
		unsigned long						_flags;
		unsigned long						_id;
		unsigned long						_revision;
		unsigned long						_unknownL;
		unsigned short						_version;
		unsigned short						_unknownS;

											TesRecordMain(TesFileType const fileType);
		virtual								~TesRecordMain();
		
		//  override TesRecordBase
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
		virtual	void						dump(const short depth);
		virtual	TesRecordBase*				findSubRecord(string const token);
		virtual	bool						compressed();
};

#endif	/* TESRECORDMAIN_H */