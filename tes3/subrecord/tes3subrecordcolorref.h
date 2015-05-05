#ifndef TES3SUBRECORDCOLORREF_H
#define	TES3SUBRECORDCOLORREF_H

#include "tes3/subrecord/tes3subrecordsingleulong.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordColorRef : public Tes3SubRecordSingleULong
{
	public:
											Tes3SubRecordColorRef(unsigned char* pBuffer);
		virtual								~Tes3SubRecordColorRef();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDCOLORREF_H */