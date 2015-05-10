#ifndef TES3SUBRECORDVTEX_H
#define	TES3SUBRECORDVTEX_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordVTEX : public TesRecordSub
{
	public:
		unsigned short						_texIds[16][16];
		unsigned short						_texStd[16][16];

											Tes3SubRecordVTEX(unsigned char* pBuffer);
		virtual								~Tes3SubRecordVTEX();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDVTEX_H */