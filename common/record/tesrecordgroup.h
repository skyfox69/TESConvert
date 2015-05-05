#ifndef TESRECORDGROUP_H
#define	TESRECORDGROUP_H

#include "common/record/tesrecordbase.h"
#include "common/util/endian.h"
#include <vector>

//-----------------------------------------------------------------------------
class TesRecordGroup : public TesRecordBase, public Endian, public vector<TesRecordBase*>
{
	public:
		string								_labelS;
		unsigned long						_labelL;
		unsigned long						_groupType;
		unsigned short						_timestamp;
		unsigned short						_version;
		unsigned short						_unknown[2];

											TesRecordGroup(TesFileType const fileType);
		virtual								~TesRecordGroup();
		
		//  override TesRecordBase
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
		virtual	void						dump(const short depth);
		virtual	TesRecordBase*				findSubRecord(string const token) { return nullptr; }
};

#endif	/* TESRECORDGROUP_H */