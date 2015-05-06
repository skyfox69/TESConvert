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
		virtual								~Tes4SubRecordSingleUShort();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDSINGLEUSHORT_H */
