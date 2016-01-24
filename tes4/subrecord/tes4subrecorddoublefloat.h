#ifndef TES4SUBRECORDDOUBLEFLOAT_H
#define	TES4SUBRECORDDOUBLEFLOAT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDoubleFloat : public TesRecordSub
{
	public:
		float								_value1;
		float								_value2;

											Tes4SubRecordDoubleFloat(unsigned char* pBuffer);
		virtual								~Tes4SubRecordDoubleFloat();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDDOUBLEFLOAT_H */
