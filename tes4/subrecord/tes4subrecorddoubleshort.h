#ifndef TES4SUBRECORDDOUBLESHORT_H
#define	TES4SUBRECORDDOUBLESHORT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDoubleShort : public TesRecordSub
{
	public:
		short								_value1;
		short								_value2;

											Tes4SubRecordDoubleShort(unsigned char* pBuffer);
		virtual								~Tes4SubRecordDoubleShort();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDDOUBLESHORT_H */
