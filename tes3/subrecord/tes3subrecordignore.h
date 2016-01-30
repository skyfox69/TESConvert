#ifndef TES3SUBRECORDIGNORE_H
#define	TES3SUBRECORDIGNORE_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordIgnore : public TesRecordSub
{
	public:
											Tes3SubRecordIgnore(unsigned char* pBuffer);
		virtual								~Tes3SubRecordIgnore();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDIGNORE_H */