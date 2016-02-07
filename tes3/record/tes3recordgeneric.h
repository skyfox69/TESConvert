#ifndef TES3RECORDGENERIC_H
#define	TES3RECORDGENERIC_H

#include "common/record/tesrecordmain.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3RecordGeneric : public TesRecordMain
{
	public:
											Tes3RecordGeneric(unsigned char* pBuffer);
		virtual								~Tes3RecordGeneric();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordMain
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3RECORDGENERIC_H */