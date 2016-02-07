#ifndef TES4SUBRECORDSINGLEULONG_H
#define	TES4SUBRECORDSINGLEULONG_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSingleULong : public TesRecordSub
{
	public:
		unsigned long						_value;

											Tes4SubRecordSingleULong(unsigned char* pBuffer);
											Tes4SubRecordSingleULong(string const name, unsigned long const value);
		virtual								~Tes4SubRecordSingleULong();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
		virtual	unsigned char*				writeMem(unsigned char* pMemory);
};

#endif	/* TES4SUBRECORDSINGLEULONG_H */
