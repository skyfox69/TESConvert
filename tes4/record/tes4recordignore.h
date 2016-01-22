#ifndef TES4RECORDIGNORE_H
#define	TES4RECORDIGNORE_H

#include "common/record/tesrecordmain.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4RecordIgnore : public TesRecordMain
{
	public:
											Tes4RecordIgnore(unsigned char* pBuffer);
		virtual								~Tes4RecordIgnore();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordMain
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
};

#endif	/* TES4RECORDIGNORE_H */