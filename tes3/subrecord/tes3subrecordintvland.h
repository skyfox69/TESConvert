#ifndef TES3SUBRECORDINTVLAND_H
#define	TES3SUBRECORDINTVLAND_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordINTVLAND : public TesRecordSub
{
	public:
		long								_cellX;
		long								_cellY;

											Tes3SubRecordINTVLAND(unsigned char* pBuffer);
		virtual								~Tes3SubRecordINTVLAND();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDINTVLAND_H */