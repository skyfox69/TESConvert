#ifndef TES4SUBRECORDSINGLEFLOAT_H
#define	TES4SUBRECORDSINGLEFLOAT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSingleFloat : public TesRecordSub
{
	public:
		unsigned long						_valueLong;
		float								_value;

											Tes4SubRecordSingleFloat(unsigned char* pBuffer);
		virtual								~Tes4SubRecordSingleFloat();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDSINGLEFLOAT_H */
