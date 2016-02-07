#ifndef	TESFUNCTIONTYPES_H
#define	TESFUNCTIONTYPES_H

#include <map>
#include <string>
#include <functional>
#include <type_traits>

using namespace std;

//-----------------------------------------------------------------------------
struct TesFillFuncIn
{
	long	_sizeMinX;
	long	_sizeMaxX;
	long	_sizeMinY;
	long	_sizeMaxY;
	size_t	_sizeX;
	size_t	_sizeY;
};

//-----------------------------------------------------------------------------
class TesRecordBase;
typedef TesRecordBase* (*TesCreateFunction)(unsigned char*);

//-----------------------------------------------------------------------------
class Tes3Processor;
class Bitmap;
using Tes3FillFunction = function<bool (Tes3Processor*, Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)>;

//-----------------------------------------------------------------------------
class Tes4Processor;
class Bitmap;
using Tes4FillFunction = function<bool (Tes4Processor*, Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)>;

#endif  /* TESFUNCTIONTYPES_H */