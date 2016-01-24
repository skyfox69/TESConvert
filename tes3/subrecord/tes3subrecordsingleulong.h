#ifndef TES3SUBRECORDSINGLEULONG_H
#define	TES3SUBRECORDSINGLEULONG_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordSingleULong : public TesRecordSub
{
	public:
		unsigned long						_value;

											Tes3SubRecordSingleULong(unsigned char* pBuffer);
		virtual								~Tes3SubRecordSingleULong();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES3SUBRECORDSINGLEULONG_H */