#ifndef TES3SUBRECORDAMBI_H
#define	TES3SUBRECORDAMBI_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordAMBI : public TesRecordSub
{
	public:
		unsigned long						_ambient;
		unsigned long						_sunlight;
		unsigned long						_fog;
		float								_fogDensity;

											Tes3SubRecordAMBI(unsigned char* pBuffer);
		virtual								~Tes3SubRecordAMBI();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDAMBI_H */