#ifndef TES4RECORDGROUP_H
#define	TES4RECORDGROUP_H

#include "common/record/tesrecordgroup.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4RecordGroup : public TesRecordGroup
{
	public:
											Tes4RecordGroup(unsigned char* pBuffer);
		virtual								~Tes4RecordGroup();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordGroup
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
		virtual	void						dump(const short depth);
};

#endif	/* TES4RECORDGROUP_H */
