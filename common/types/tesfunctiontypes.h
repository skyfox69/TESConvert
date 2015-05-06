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
using Tes3FillFunction = function<bool (Tes3Processor*, unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap)>;

//-----------------------------------------------------------------------------
class Tes4Processor;
using Tes4FillFunction = function<bool (Tes4Processor*, unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap)>;

#endif  /* TESFUNCTIONTYPES_H */