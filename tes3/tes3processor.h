#ifndef	TES3PROCESSOR_H
#define	TES3PROCESSOR_H

#include "common/tesparser.h"
#include "common/types/tesfunctiontypes.h"
#include <map>

//-----------------------------------------------------------------------------
class Tes3Processor
{
	private:
		map<string, vector<TesRecordBase*>>&	_mapRecords;

		virtual	bool							prepareData();
		virtual	bool							dumpToMap(const string fileName, Tes3FillFunction pFillFunction);
		virtual	bool							dumpVhgt(unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap);
		virtual	bool							dumpVclr(unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap);
		virtual	bool							dumpVtex(unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap);

	public:
												Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords);
		virtual									~Tes3Processor();

		virtual	bool							dumpVclrMap(string const fileName);
		virtual	bool							dumpVhgtMap(string const fileName);
		virtual	bool							dumpVtexMap(string const fileName);
};
#endif  /* TES3PROCESSOR_H */
