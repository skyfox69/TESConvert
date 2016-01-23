#ifndef	TES3PROCESSOR_H
#define	TES3PROCESSOR_H

#include "common/itesprocessor.h"
#include "common/tesparser.h"
#include "common/types/tesfunctiontypes.h"
#include <map>

//-----------------------------------------------------------------------------
struct Tes3FillFuncIn
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
class Tes3Processor : public ITesProcessor
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;

		virtual	bool							prepareData();
		virtual	bool							dumpToMap(const string fileName, Tes3FillFunction pFillFunction, unsigned short cellSize);
		virtual	bool							dumpVhgt(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn);
		virtual	bool							dumpVclr(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn);
		virtual	bool							dumpVtex(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn);

	public:
												Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords);
		virtual									~Tes3Processor();

		virtual	bool							dumpVclrMap(string const fileName) override;
		virtual	bool							dumpVhgtMap(string const fileName) override;
		virtual	bool							dumpVtexMap(string const fileName) override;
};
#endif  /* TES3PROCESSOR_H */
