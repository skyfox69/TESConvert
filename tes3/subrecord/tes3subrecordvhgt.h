#ifndef TES3SUBRECORDVHGT_H
#define	TES3SUBRECORDVHGT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordVHGT : public TesRecordSub
{
	public:
		unsigned char						_height[65][65];
		float								_offset;
		unsigned char						_unknown[3];

											Tes3SubRecordVHGT(unsigned char* pBuffer);
		virtual								~Tes3SubRecordVHGT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES3SUBRECORDVHGT_H */