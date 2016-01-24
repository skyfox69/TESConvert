#ifndef TES4SUBRECORDHEDR_H
#define	TES4SUBRECORDHEDR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordHEDR : public TesRecordSub
{
	public:
		float								_version;
		unsigned long						_numRecords;
		unsigned long						_nextObjectId;

											Tes4SubRecordHEDR(unsigned char* pBuffer);
		virtual								~Tes4SubRecordHEDR();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDHEDR_H */