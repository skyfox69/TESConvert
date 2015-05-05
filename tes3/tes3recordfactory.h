#ifndef	TES3RECORDFACTORY_H
#define	TES3RECORDFACTORY_H

#include "common/itesrecordfactory.h"
#include "common/types/tesfunctiontypes.h"

//-----------------------------------------------------------------------------
class Tes3RecordFactory : public ITesRecordFactory
{
	private:
		map<string, TesCreateFunction>		_mapKnownRecords;

		virtual void						registerClasses();
	public:
											Tes3RecordFactory();
		virtual								~Tes3RecordFactory();

		//  ITesRecordFactory
		virtual	TesRecordBase*				create(string const& token, string const& tokenMain, unsigned char* pBuffer);
};
#endif  /* TES3RECORDFACTORY_H */