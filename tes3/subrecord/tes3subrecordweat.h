#ifndef TES3SUBRECORDWEAT_H
#define	TES3SUBRECORDWEAT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordWEAT : public TesRecordSub
{
	public:
		unsigned char						_clear;
		unsigned char						_cloudy;
		unsigned char						_foggy;
		unsigned char						_overcast;
		unsigned char						_rain;
		unsigned char						_thunder;
		unsigned char						_ash;
		unsigned char						_blight;

											Tes3SubRecordWEAT(unsigned char* pBuffer);
		virtual								~Tes3SubRecordWEAT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDWEAT_H */