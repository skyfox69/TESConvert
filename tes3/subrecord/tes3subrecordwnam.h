#ifndef TES3SUBRECORDWNAM_H
#define	TES3SUBRECORDWNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordWNAM : public TesRecordSub
{
	public:
		unsigned char						_data[9][9];

											Tes3SubRecordWNAM(unsigned char* pBuffer);
		virtual								~Tes3SubRecordWNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES3SUBRECORDWNAM_H */