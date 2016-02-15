#ifndef	TES4PROCESSOR_H
#define	TES4PROCESSOR_H

#include "common/itesprocessor.h"
#include "common/tesparser.h"
#include "common/types/tesfunctiontypes.h"
#include "common/util/verbosity.h"
#include <map>

class Tes4RecordGeneric;
class Tes4RecordGroup;

//-----------------------------------------------------------------------------
class Tes4Processor : protected Verbosity, public ITesProcessor
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;		//  all records by name
		map<string, Tes4RecordGeneric*>			_mapRecordsLand;
		map<unsigned long, Tes4RecordGeneric*>	_mapRecordsCell;	//  CELL records
		map<unsigned long, Tes4RecordGroup*>	_mapRecordsGrpWrld;	//  Groups WRLD Children
		map<unsigned long, Tes4RecordGroup*>	_mapRecordsGrpCell;	//  Groups external CELL Children
		vector<TesRecordBase*>&					_records;			//  all records by structure/appearance
		
		virtual	bool							prepareData();
		virtual	bool							prepareDataRecursive(vector<TesRecordBase*>& records, Tes4RecordGroup* pGroup = nullptr);
		virtual	bool							prepareLandMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize);
		virtual	bool							dumpToMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize);
		virtual	bool							dumpVhgt(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);
		virtual	bool							dumpVclr(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);
		virtual	bool							dumpVtex(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);

	public:
												Tes4Processor(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records);
		virtual									~Tes4Processor();

		virtual	bool							dumpVclrMap    (string const fileName) override;
		virtual	bool							dumpVhgtMap    (string const fileName) override;
		virtual	bool							dumpVtexMap    (string const fileName) override;
		virtual	bool							dumpWorldspaces() override;

		virtual	Bitmap*							generateVHGTBitmap();
		virtual	Bitmap*							generateVCLRBitmap();
};
#endif  /* TES4PROCESSOR_H */
