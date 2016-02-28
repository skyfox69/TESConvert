#ifndef TESMAPPINGSTORAGE_H
#define	TESMAPPINGSTORAGE_H

#include "common/util/verbosity.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class	Tes4RecordGeneric;

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
		static	TESMappingStorage*					_pInstance;
		char*										_pCursor;
		map<string, unsigned long>					_mapPseudoIds;

	protected:
													TESMappingStorage();
		virtual	string								tokenString();
		virtual	unsigned long						tokenULong ();
		virtual	unsigned short						tokenUShort();
		virtual	unsigned char						tokenUChar();
		virtual	unsigned long						tokenFormId();

		virtual	void								createTXST();
		virtual	void								createLTEX();

	public:
		map<unsigned long, TESMapTes3Ids>			_mapTes3Tes5Ids;
		map<unsigned long, Tes4RecordGeneric*>		_mapTes5Txst;
		map<unsigned long, Tes4RecordGeneric*>		_mapTes5Ltex;
		TESMapTes3Ids								_defaultEmptyId;
		TESMapTes3Ids								_defaultTes5Id;
		TESMapTes3Ids								_defaultMattId;

		virtual										~TESMappingStorage();
		static	TESMappingStorage*					getInstance();

		virtual	bool								initialize();
		virtual	TESMapTes3Ids&						mapTes3Id(unsigned long const tes3Id, vector<Tes4RecordGeneric*>& usedLTEXs, vector<Tes4RecordGeneric*>& usedTXSTs);
};
#endif  /* TESMAPPINGSTORAGE_H */
