#ifndef TES3SUBRECORDSINGLESTRING_H
#define	TES3SUBRECORDSINGLESTRING_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordSingleString : public TesRecordSub
{
	public:
		string								_text;

											Tes3SubRecordSingleString(unsigned char* pBuffer);
		virtual								~Tes3SubRecordSingleString();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDSINGLESTRING_H */