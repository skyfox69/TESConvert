#ifndef TES4SUBRECORDWRLDMNAM_H
#define	TES4SUBRECORDWRLDMNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordWRLDMNAM : public TesRecordSub
{
	public:
		unsigned long						_width;
		unsigned long						_height;
		short								_cellNwX;
		short								_cellNwY;
		short								_cellSeX;
		short								_cellSeY;
		float								_camHeightMin;
		float								_camHeightMax;
		float								_camInitPitch;

											Tes4SubRecordWRLDMNAM();
											Tes4SubRecordWRLDMNAM(unsigned char* pBuffer);
		virtual								~Tes4SubRecordWRLDMNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDWRLDMNAM_H */
