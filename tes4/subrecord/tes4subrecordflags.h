#ifndef TES4SUBRECORDFLAGS_H
#define	TES4SUBRECORDFLAGS_H

#include "tes4/subrecord/tes4subrecordsingleulong.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordFlags : public Tes4SubRecordSingleULong
{
	public:
											Tes4SubRecordFlags(unsigned char* pBuffer);
		virtual								~Tes4SubRecordFlags();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDFLAGS_H */