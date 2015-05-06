#ifndef TES3SUBRECORDDATACELL_H
#define	TES3SUBRECORDDATACELL_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordDATACELL : public TesRecordSub
{
	public:
		unsigned long						_flags;
		long								_gridX;
		long								_gridY;

											Tes3SubRecordDATACELL(unsigned char* pBuffer);
		virtual								~Tes3SubRecordDATACELL();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES3SUBRECORDDATACELL_H */