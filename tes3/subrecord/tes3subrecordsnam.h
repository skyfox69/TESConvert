#ifndef TES3SUBRECORDSNAM_H
#define	TES3SUBRECORDSNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordSNAM : public TesRecordSub
{
	public:
		string								_text;
		unsigned char						_chance;

											Tes3SubRecordSNAM(unsigned char* pBuffer);
		virtual								~Tes3SubRecordSNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDSNAM_H */