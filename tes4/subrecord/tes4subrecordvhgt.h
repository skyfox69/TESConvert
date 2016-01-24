#ifndef TES4SUBRECORDVHGT_H
#define	TES4SUBRECORDVHGT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordVHGT : public TesRecordSub
{
	public:
		unsigned char						_height[33][33];
		float								_offset;
		unsigned char						_unknown[4];

											Tes4SubRecordVHGT(unsigned char* pBuffer);
		virtual								~Tes4SubRecordVHGT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDVHGT_H */