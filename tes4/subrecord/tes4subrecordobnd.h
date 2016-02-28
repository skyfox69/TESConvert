#ifndef TES4SUBRECORDOBND_H
#define	TES4SUBRECORDOBND_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordOBND : public TesRecordSub
{
	public:
		unsigned char						_unknown[12];

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