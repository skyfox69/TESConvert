#ifndef TES4SUBRECORDTRIPLEFLOAT_H
#define	TES4SUBRECORDTRIPLEFLOAT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordTripleFloat : public TesRecordSub
{
	public:
		float								_value1;
		float								_value2;
		float								_value3;

											Tes4SubRecordTripleFloat(unsigned char* pBuffer);
		virtual								~Tes4SubRecordTripleFloat();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDTRIPLEFLOAT_H */
