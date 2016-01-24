#ifndef TES4SUBRECORDDOUBLEUCHAR_H
#define	TES4SUBRECORDDOUBLEUCHAR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDoubleUChar : public TesRecordSub
{
	public:
		unsigned char						_value1;
		unsigned char						_value2;

											Tes4SubRecordDoubleUChar(unsigned char* pBuffer);
		virtual								~Tes4SubRecordDoubleUChar();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDDOUBLEUCHAR_H */
