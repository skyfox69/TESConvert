#ifndef TES4SUBRECORDDNAM_H
#define	TES4SUBRECORDDNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDNAM : public TesRecordSub
{
	public:
		float								_angle;
		unsigned long						_formId;

											Tes4SubRecordDNAM(unsigned char* pBuffer);
		virtual								~Tes4SubRecordDNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDDNAM_H */