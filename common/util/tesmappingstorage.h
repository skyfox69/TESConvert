#ifndef TESMAPPINGSTORAGE_H
#define	TESMAPPINGSTORAGE_H

#include "common/util/verbosity.h"
#include <string>
#include <map>

using namespace std;

//-----------------------------------------------------------------------------
struct TESMapTes3Ids
{
	string				_masterName;
	unsigned long		_idTes5 = 0;
};

//-----------------------------------------------------------------------------
class TESMappingStorage : protected Verbosity
{
	enum class TESMappingSection : std::int8_t { UNKNOWN = 0, TES3TES5 = 1, TES5MATT = 2, TES5TXST = 3, TES5LTEX = 4, DEFAULTS = 5  };

	private:
		static	TESMappingStorage*			_pInstance;
		char*								_pCursor;

	protected:
											TESMappingStorage();
		virtual	string						tokenString();
		virtual	unsigned long				tokenULong ();

	public:
		map<unsigned long, TESMapTes3Ids>	_mapTes3Tes5Ids;
		TESMapTes3Ids						_defaultTes5Id;

		virtual								~TESMappingStorage();
		static	TESMappingStorage*			getInstance();

		virtual	bool						initialize();
		virtual	TESMapTes3Ids&				mapTes3Id(unsigned long const tes3Id);
};
#endif  /* TESMAPPINGSTORAGE_H */
