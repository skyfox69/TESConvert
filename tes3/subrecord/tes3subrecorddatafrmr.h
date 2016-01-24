#ifndef TES3SUBRECORDDATAFRMR_H
#define	TES3SUBRECORDDATAFRMR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordDATAFRMR : public TesRecordSub
{
	public:
		float								_posX;
		float								_posY;
		float								_posZ;
		float								_rotX;
		float								_rotY;
		float								_rotZ;

											Tes3SubRecordDATAFRMR(unsigned char* pBuffer);
		virtual								~Tes3SubRecordDATAFRMR();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES3SUBRECORDDATAFRMR_H */