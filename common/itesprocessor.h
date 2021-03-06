#ifndef	ITESPROCESSOR_H
#define	ITESPROCESSOR_H

#include <string>

using namespace std;

class Bitmap;

//-----------------------------------------------------------------------------
class ITesProcessor
{
	public:
												ITesProcessor() {};
		virtual									~ITesProcessor() {};

		virtual	bool							dumpVclrMap    (string const fileName) = 0;
		virtual	bool							dumpVhgtMap    (string const fileName) = 0;
		virtual	bool							dumpVtexMap    (string const fileName) = 0;
		virtual	bool							dumpWorldspaces() = 0;

		virtual	Bitmap*							generateVHGTBitmap() = 0;
		virtual	Bitmap*							generateVCLRBitmap() = 0;
		virtual	Bitmap*							generateVTEXBitmap() = 0;
};
#endif  /* ITESPROCESSOR_H */
