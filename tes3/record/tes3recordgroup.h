#ifndef TES3RECORDGROUP_H
#define	TES3RECORDGROUP_H

#include "common/record/tesrecordgroup.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3RecordGroup : public TesRecordGroup
{
	public:
		unsigned long						_objIndex;
		
											Tes3RecordGroup(unsigned char* pBuffer);
		virtual								~Tes3RecordGroup();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordGroup
		virtual	size_t						sizeRecord() override;
		virtual	size_t						sizeTotal() override;
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3RECORDGROUP_H */