#ifndef TES4SUBRECORDSINGLEUSHORT_H
#define	TES4SUBRECORDSINGLEUSHORT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSingleUShort : public TesRecordSub
{
	public:
		unsigned short						_value;

											Tes4SubRecordSingleUShort(unsigned char* pBuffer);
											Tes4SubRecordSingleUShort(string const name, unsigned short const value);
		virtual								~Tes4SubRecordSingleUShort();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDSINGLEUSHORT_H */
