#ifndef TES3SUBRECORDDATATES3_H
#define	TES3SUBRECORDDATATES3_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordDATATES3 : public TesRecordSub
{
	public:
		long								_value;

											Tes3SubRecordDATATES3(unsigned char* pBuffer);
		virtual								~Tes3SubRecordDATATES3();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDDATATES3_H */