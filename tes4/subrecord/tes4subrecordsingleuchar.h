#ifndef TES4SUBRECORDSINGLEUCHAR_H
#define	TES4SUBRECORDSINGLEUCHAR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordSingleUChar : public TesRecordSub
{
	public:
		unsigned char						_value;

											Tes4SubRecordSingleUChar(unsigned char* pBuffer);
		virtual								~Tes4SubRecordSingleUChar();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDSINGLEUCHAR_H */
