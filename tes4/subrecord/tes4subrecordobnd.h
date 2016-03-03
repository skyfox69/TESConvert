#ifndef TES4SUBRECORDOBND_H
#define	TES4SUBRECORDOBND_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordOBND : public TesRecordSub
{
	public:
		short								_x1;
		short								_y1;
		short								_z1;
		short								_x2;
		short								_y2;
		short								_z2;

											Tes4SubRecordOBND(unsigned char* pBuffer);
											Tes4SubRecordOBND();
		virtual								~Tes4SubRecordOBND();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDOBND_H */