#ifndef TES4SUBRECORDSINGLESTRING_H
#define	TES4SUBRECORDSINGLESTRING_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSingleString : public TesRecordSub
{
	public:
		string								_text;

											Tes4SubRecordSingleString(unsigned char* pBuffer);
		virtual								~Tes4SubRecordSingleString();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDSINGLESTRING_H */
