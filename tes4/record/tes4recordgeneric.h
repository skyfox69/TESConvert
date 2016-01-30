#ifndef TES4RECORDGENERIC_H
#define	TES4RECORDGENERIC_H

#include "common/record/tesrecordmain.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4RecordGeneric : public TesRecordMain
{
	private:
		unsigned char*						_pDataBuffer;
		
	public:
											Tes4RecordGeneric(unsigned char* pBuffer);
											Tes4RecordGeneric(string const name, unsigned long const id);
		virtual								~Tes4RecordGeneric();
		
		//  TesRecordFactory
		static	TesRecordBase*				create(unsigned char* pBuffer);
		static	void						registerClass(map<string, TesCreateFunction>& mapRecords);

		//  override TesRecordMain
		virtual	size_t						sizeRecord();
		virtual	size_t						sizeTotal();
		virtual	size_t						calcSizes();

		//  override TesRecordBase
		virtual	void						writeFile(FILE* pFile);
};

#endif	/* TES4RECORDGENERIC_H */