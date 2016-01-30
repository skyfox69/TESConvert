#ifndef TES4SUBRECORDDODT_H
#define	TES4SUBRECORDDODT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDODT : public TesRecordSub
{
	public:
		float								_widthMin;
		float								_widthMax;
		float								_heightMin;
		float								_heightMax;
		float								_depth;
		float								_shininess;
		float								_parallaxScale;
		unsigned long						_rgb;
		unsigned char						_parallaxPasses;
		unsigned char						_flags;
		unsigned char						_unknown[2];

											Tes4SubRecordDODT(unsigned char* pBuffer);
		virtual								~Tes4SubRecordDODT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDDODT_H */