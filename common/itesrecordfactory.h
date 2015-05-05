#ifndef	ITESRECORDFACTORY_H
#define	ITESRECORDFACTORY_H

#include <string>

using namespace std;

class TesRecordBase;

//-----------------------------------------------------------------------------
class ITesRecordFactory
{
	public:
											ITesRecordFactory() {};
		virtual								~ITesRecordFactory() {};
		virtual	TesRecordBase*				create(string const& token, string const& tokenMain, unsigned char* pBuffer) = 0;
};
#endif  /* ITESRECORDFACTORY_H */