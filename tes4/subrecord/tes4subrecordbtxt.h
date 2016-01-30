#ifndef TES4SUBRECORDBTXT_H
#define	TES4SUBRECORDBTXT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordBTXT : public TesRecordSub
{
	public:
		unsigned long						_textureId;
		unsigned char						_quadrant;
		unsigned char						_unknown[3];

											Tes4SubRecordBTXT(unsigned char* pBuffer);
		virtual								~Tes4SubRecordBTXT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDBTXT_H */