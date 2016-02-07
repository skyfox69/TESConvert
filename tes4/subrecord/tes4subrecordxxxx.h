#ifndef TES4SUBRECORDXXXX_H
#define	TES4SUBRECORDXXXX_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordXXXX : public TesRecordSub
{
	public:
		unsigned long						_dataSize;

											Tes4SubRecordXXXX(unsigned char* pBuffer);
		virtual								~Tes4SubRecordXXXX();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDXXXX_H */