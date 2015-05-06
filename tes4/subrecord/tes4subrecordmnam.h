#ifndef TES4SUBRECORDMNAM_H
#define	TES4SUBRECORDMNAM_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordMNAM : public TesRecordSub
{
	public:
		unsigned long						_width;
		unsigned long						_height;
		short								_cellNwX;
		short								_cellNwY;
		short								_cellSeX;
		short								_cellSeY;
		float								_camHeightMin;
		float								_camHeightMax;
		float								_camInitPitch;

											Tes4SubRecordMNAM(unsigned char* pBuffer);
		virtual								~Tes4SubRecordMNAM();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDMNAM_H */
