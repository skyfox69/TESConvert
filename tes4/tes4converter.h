#ifndef	TES4CONVERTER_H
#define	TES4CONVERTER_H

#include "common/tesparser.h"
#include "common/util/verbosity.h"
#include <map>

class	Tes4SubRecordMNAM;
class	Bitmap;

//-----------------------------------------------------------------------------
class Tes4Converter : protected Verbosity
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;		//  all records by name
		map<string, TesRecordBase*>				_mapRecordsLands;	//  all land records by coordinates
		vector<TesRecordBase*>&					_records;			//  all records by structure/appearance
		string									_worldspace;
		unsigned long							_objectId;			//  unique object id

		virtual	void							prepareData(Tes4SubRecordMNAM* pSubMNAM);
		
	public:
												Tes4Converter(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records, string const worldspace);
		virtual									~Tes4Converter();

		virtual	bool							convert(string const fileName, Bitmap* pBitmapVHGT, Bitmap* pBitmapVCLR, Bitmap* pBitmapVTEX);
};
#endif  /* TES4CONVERTER_H */
