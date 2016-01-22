#ifndef TES4SUBRECORDIGNORE_H
#define	TES4SUBRECORDIGNORE_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordIgnore : public TesRecordSub
{
	public:
											Tes4SubRecordIgnore(unsigned char* pBuffer);
		virtual								~Tes4SubRecordIgnore();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDIGNORE_H */
