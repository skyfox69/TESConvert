#ifndef TES4SUBRECORDATXT_H
#define	TES4SUBRECORDATXT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordATXT : public TesRecordSub
{
	public:
		unsigned long						_textureId;
		unsigned short						_layer;
		unsigned char						_quadrant;
		unsigned char						_unknown;

											Tes4SubRecordATXT(unsigned char* pBuffer);
		virtual								~Tes4SubRecordATXT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDATXT_H */