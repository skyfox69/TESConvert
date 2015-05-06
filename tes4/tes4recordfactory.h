#ifndef	TES4RECORDFACTORY_H
#define	TES4RECORDFACTORY_H

#include "common/itesrecordfactory.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes4RecordFactory : public ITesRecordFactory
{
	private:
		map<string, TesCreateFunction>		_mapKnownRecords;

		virtual void						registerClasses();
	public:
											Tes4RecordFactory();
		virtual								~Tes4RecordFactory();

		//  ITesRecordFactory
		virtual	TesRecordBase*				create(string const& token, string const& tokenMain, unsigned char* pBuffer);
};
#endif  /* TES4RECORDFACTORY_H */