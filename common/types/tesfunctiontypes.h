#ifndef	TESFUNCTIONTYPES_H
#define	TESFUNCTIONTYPES_H

#include <map>
#include <string>
#include <functional>
#include <type_traits>

using namespace std;

//-----------------------------------------------------------------------------
class TesRecordBase;
typedef TesRecordBase* (*TesCreateFunction)(unsigned char*);

//-----------------------------------------------------------------------------
class Tes3Processor;
class Bitmap;
struct Tes3FillFuncIn;
using Tes3FillFunction = function<bool (Tes3Processor*, Bitmap* pBitmap, Tes3FillFuncIn* pFillFuncIn)>;

//-----------------------------------------------------------------------------
class Tes4Processor;
class Bitmap;
struct Tes4FillFuncIn;
using Tes4FillFunction = function<bool (Tes4Processor*, Bitmap* pBitmap, Tes4FillFuncIn* pFillFuncIn)>;

#endif  /* TESFUNCTIONTYPES_H */