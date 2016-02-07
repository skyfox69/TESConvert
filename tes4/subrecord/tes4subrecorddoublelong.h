#ifndef TES4SUBRECORDDOUBLELONG_H
#define	TES4SUBRECORDDOUBLELONG_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDoubleLong : public TesRecordSub
{
	public:
		long								_value[2];

											Tes4SubRecordDoubleLong(unsigned char* pBuffer);
											Tes4SubRecordDoubleLong(string const name, long const value1, long const value2);
		virtual								~Tes4SubRecordDoubleLong();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDDOUBLELONG_H */
