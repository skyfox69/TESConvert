#ifndef TES4SUBRECORDREFRDATA_H
#define	TES4SUBRECORDREFRDATA_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordREFRDATA : public TesRecordSub
{
	public:
		float								_posX;
		float								_posY;
		float								_posZ;
		float								_rotX;
		float								_rotY;
		float								_rotZ;

											Tes4SubRecordREFRDATA(unsigned char* pBuffer);
		virtual								~Tes4SubRecordREFRDATA();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDREFRDATA_H */