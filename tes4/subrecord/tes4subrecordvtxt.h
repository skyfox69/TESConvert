#ifndef TES4SUBRECORDVTXT_H
#define	TES4SUBRECORDVTXT_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordVTXT : public TesRecordSub
{
	public:
		struct EntryVTXT
		{
			float				_opacity;
			unsigned short		_position;
			unsigned char		_unknown1;
			unsigned char		_unknown2;
		};

		EntryVTXT*							_pEntries;
		size_t								_count;

											Tes4SubRecordVTXT(unsigned char* pBuffer);
		virtual								~Tes4SubRecordVTXT();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth);
};

#endif	/* TES4SUBRECORDVTXT_H */