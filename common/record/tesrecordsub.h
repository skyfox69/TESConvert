#ifndef TESRECORDSUB_H
#define	TESRECORDSUB_H

#include "common/record/tesrecordbase.h"
#include "common/util/endian.h"

//-----------------------------------------------------------------------------
class TesRecordSub : public TesRecordBase, public Endian
{
	public:
											TesRecordSub(TesFileType const fileType);
		virtual								~TesRecordSub();
		
		//  override TesRecordBase
		virtual	size_t						sizeRecord() override;
		virtual	size_t						sizeTotal() override;
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
		virtual	TesRecordBase*				findSubRecord(string const token) { return nullptr; }
};

#endif	/* TESRECORDSUB_H */