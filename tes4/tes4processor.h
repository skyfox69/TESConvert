#ifndef	TES4PROCESSOR_H
#define	TES4PROCESSOR_H

#include "common/tesparser.h"
#include "common/types/tesfunctiontypes.h"
#include <map>

class Tes4RecordGeneric;
class Tes4RecordGroup;

//-----------------------------------------------------------------------------
struct Tes4FillFuncIn
{
	long	_sizeMinX;
	long	_sizeMaxX;
	long	_sizeMinY;
	long	_sizeMaxY;
	size_t	_sizeX;
	size_t	_sizeY;
	size_t	_sizeMap;
};

//-----------------------------------------------------------------------------
class Tes4Processor
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;
		map<string, Tes4RecordGeneric*>			_mapRecordsLand;
		vector<TesRecordBase*>&					_records;

		virtual	bool							prepareData();
		virtual	bool							prepareDataRecursive(vector<TesRecordBase*>& records, map<unsigned long, Tes4RecordGeneric*>& mapRecordIds, Tes4RecordGroup* pGroup = nullptr);
		virtual	bool							dumpToMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize);
		virtual	bool							dumpVhgt(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn);
		virtual	bool							dumpVclr(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn);
		virtual	bool							dumpVtex(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn);

	public:
												Tes4Processor(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records);
		virtual									~Tes4Processor();

		virtual	bool							dumpVclrMap(string const fileName);
		virtual	bool							dumpVhgtMap(string const fileName);
		virtual	bool							dumpVtexMap(string const fileName);
};
#endif  /* TES4PROCESSOR_H */
