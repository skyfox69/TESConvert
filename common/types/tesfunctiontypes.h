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
struct Tes3FillFuncIn;
using Tes3FillFunction = function<bool (Tes3Processor*, unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn)>;

//-----------------------------------------------------------------------------
class Tes4Processor;
struct Tes4FillFuncIn;
using Tes4FillFunction = function<bool (Tes4Processor*, unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn)>;

#endif  /* TESFUNCTIONTYPES_H */