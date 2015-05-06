#ifndef TES3SUBRECORDSINGLEFLOAT_H
#define	TES3SUBRECORDSINGLEFLOAT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordSingleFloat : public TesRecordSub
{
	public:
		float								_value;

											Tes3SubRecordSingleFloat(unsigned char* pBuffer);
		virtual								~Tes3SubRecordSingleFloat();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDSINGLEFLOAT_H */