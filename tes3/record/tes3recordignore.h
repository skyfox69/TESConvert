#ifndef TES3RECORDIGNORE_H
#define	TES3RECORDIGNORE_H

#include "common/record/tesrecordmain.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3RecordIgnore : public TesRecordMain
{
	public:
											Tes3RecordIgnore(unsigned char* pBuffer);
		virtual								~Tes3RecordIgnore();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordMain
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
		virtual	void						dump(const short depth);
};

#endif	/* TES3RECORDIGNORE_H */