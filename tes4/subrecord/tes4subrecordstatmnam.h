#ifndef TES4SUBRECORDSTATMNAM_H
#define	TES4SUBRECORDSTATMNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSTATMNAM : public TesRecordSub
{
	public:
		string								_modelLOD[4];

											Tes4SubRecordSTATMNAM();
											Tes4SubRecordSTATMNAM(unsigned char* pBuffer);
		virtual								~Tes4SubRecordSTATMNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDSTATMNAM_H */
