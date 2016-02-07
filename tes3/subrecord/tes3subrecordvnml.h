#ifndef TES3SUBRECORDVNML_H
#define	TES3SUBRECORDVNML_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3SubRecordVNML : public TesRecordSub
{
	public:
		struct BufferEntry
		{
			unsigned char		_xr;
			unsigned char		_yg;
			unsigned char		_zb;
		};
		BufferEntry							_buffer[65][65];

											Tes3SubRecordVNML(unsigned char* pBuffer);
		virtual								~Tes3SubRecordVNML();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES3SUBRECORDVNML_H */