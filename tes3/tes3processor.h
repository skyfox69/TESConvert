#ifndef	TES3PROCESSOR_H
#define	TES3PROCESSOR_H

#include "common/itesprocessor.h"
#include "common/tesparser.h"
#include "common/util/verbosity.h"
#include "common/types/tesfunctiontypes.h"
#include <map>

//-----------------------------------------------------------------------------
class Tes3Processor : protected Verbosity, public ITesProcessor
{
	private:
		TesFillFuncIn*							_pFillFuncIn;
		map<string, vector<TesRecordBase*>>&	_mapRecords;

		virtual	bool							prepareData();
		virtual	bool							dumpToMap  (const string fileName, Tes3FillFunction pFillFunction, unsigned short cellSize);
		virtual	bool							dumpVhgt   (Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);
		virtual	bool							dumpVclr   (Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);
		virtual	bool							dumpVtex   (Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn);

	public:
												Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords);
		virtual									~Tes3Processor();

		virtual	bool							dumpVclrMap    (string const fileName) override;
		virtual	bool							dumpVhgtMap    (string const fileName) override;
		virtual	bool							dumpVtexMap    (string const fileName) override;
		virtual	bool							dumpWorldspaces() override;

		virtual	Bitmap*							generateVHGTBitmap();
		virtual	Bitmap*							generateVCLRBitmap();
		virtual	Bitmap*							generateVTEXBitmap();
};
#endif  /* TES3PROCESSOR_H */
