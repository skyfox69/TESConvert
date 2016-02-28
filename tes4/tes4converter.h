#ifndef	TES4CONVERTER_H
#define	TES4CONVERTER_H

#include "common/tesparser.h"
#include "common/util/verbosity.h"
#include <map>

class	Tes4SubRecordMNAM;
class	Tes4RecordGeneric;
class	Bitmap;
class	TESMapTes3Ids;

//-----------------------------------------------------------------------------
class Tes4Converter : protected Verbosity
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;		//  all records by name
		map<string, TesRecordBase*>				_mapRecordsLands;	//  all land records by coordinates
		map<unsigned long, TesRecordBase*>		_mapRecordsLtexs;	//  all ltex records by tes3 id
		vector<TesRecordBase*>&					_records;			//  all records by structure/appearance
		string									_worldspace;

		virtual	void							prepareData(Tes4SubRecordMNAM* pSubMNAM);
		virtual	TESMapTes3Ids&					createLTEX(unsigned long const tes3Id, vector<Tes4RecordGeneric*>& usedLTEXs, vector<Tes4RecordGeneric*>& usedTXSTs);
		
	public:
												Tes4Converter(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records, string const worldspace);
		virtual									~Tes4Converter();

		virtual	bool							convert(string const fileName, Bitmap* pBitmapVHGT, Bitmap* pBitmapVCLR, Bitmap* pBitmapVTEX);
};
#endif  /* TES4CONVERTER_H */
