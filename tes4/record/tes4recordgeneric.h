#ifndef TES4RECORDGENERIC_H
#define	TES4RECORDGENERIC_H

#include "common/record/tesrecordmain.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4RecordGeneric : public TesRecordMain
{
	public:
											Tes4RecordGeneric(unsigned char* pBuffer);
		virtual								~Tes4RecordGeneric();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordMain
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
};

#endif	/* TES4RECORDGENERIC_H */