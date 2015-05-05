#ifndef TES3SUBRECORDFLAGS_H
#define	TES3SUBRECORDFLAGS_H

#include "tes3/subrecord/tes3subrecordsingleulong.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordFlags : public Tes3SubRecordSingleULong
{
	public:
											Tes3SubRecordFlags(unsigned char* pBuffer);
		virtual								~Tes3SubRecordFlags();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDFLAGS_H */