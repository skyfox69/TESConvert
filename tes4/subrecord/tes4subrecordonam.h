#ifndef TES4SUBRECORDONAM_H
#define	TES4SUBRECORDONAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordONAM : public TesRecordSub
{
	public:
		float								_scale;
		float								_offsetX;
		float								_offsetY;
		float								_offsetZ;

											Tes4SubRecordONAM(unsigned char* pBuffer);
		virtual								~Tes4SubRecordONAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDONAM_H */
