#ifndef TES3SUBRECORDHEDR_H
#define	TES3SUBRECORDHEDR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordHEDR : public TesRecordSub
{
	public:
		string								_company;
		string								_description;
		float								_version;
		unsigned long						_unknown;

											Tes3SubRecordHEDR(unsigned char* pBuffer);
		virtual								~Tes3SubRecordHEDR();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDHEDR_H */