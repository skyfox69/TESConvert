#ifndef TES4SUBRECORDDOUBLEUCHAR_H
#define	TES4SUBRECORDDOUBLEUCHAR_H

#include "common/record/tesrecordsub.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4SubRecordDoubleUChar : public TesRecordSub
{
	public:
		unsigned char						_value1;
		unsigned char						_value2;

											Tes4SubRecordDoubleUChar(unsigned char* pBuffer);
											Tes4SubRecordDoubleUChar(string const name, unsigned char const value1, unsigned char const value2);
		virtual								~Tes4SubRecordDoubleUChar();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordSub
		virtual	void						dump(const short depth) override;
		virtual	void						dumpXml() override;

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4SUBRECORDDOUBLEUCHAR_H */
