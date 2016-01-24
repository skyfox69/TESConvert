#ifndef TES4SUBRECORDXCLCCELL_H
#define	TES4SUBRECORDXCLCCELL_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordXCLCCELL : public TesRecordSub
{
	public:
		long								_x;
		long								_y;
		unsigned long						_flags;

											Tes4SubRecordXCLCCELL(unsigned char* pBuffer);
		virtual								~Tes4SubRecordXCLCCELL();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;
};

#endif	/* TES4SUBRECORDXCLCCELL_H */
