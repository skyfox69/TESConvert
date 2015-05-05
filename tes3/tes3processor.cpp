#include "tes3/tes3processor.h"
#include "tes3/subrecord/tes3subrecordintvland.h"
#include "tes3/subrecord/tes3subrecordvnml.h"
#include "tes3/subrecord/tes3subrecordvhgt.h"
#include <cstring>

#define	SIZE_MAP_MAX	100
#define	SIZE_CELL		 64

//-----------------------------------------------------------------------------
Tes3Processor::Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords)
	:	_mapRecords(mapRecords)
{}

//-----------------------------------------------------------------------------
Tes3Processor::~Tes3Processor()
{}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVclrMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", "VCLR", &Tes3Processor::dumpVclr);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgtMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", "VHGT", &Tes3Processor::dumpVhgt);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpToMap(const string fileName, const string token, Tes3FillFunction pFillFunction)
{
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	long					sizeMinX    (999999);
	long					sizeMaxX    (-999999);
	long					sizeMinY    (999999);
	long					sizeMaxY    (-999999);
	size_t					sizeX       (0);
	size_t					sizeY       (0);
	size_t					sizeMap     (SIZE_MAP_MAX * SIZE_MAP_MAX);

	//  get size of map
	printf("generating bitmap file\n  getting sizes: ");
	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv) {
			if (pSubLandIntv->_cellX < sizeMinX)		sizeMinX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellX > sizeMaxX)		sizeMaxX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellY < sizeMinY)		sizeMinY = pSubLandIntv->_cellY;
			if (pSubLandIntv->_cellY > sizeMaxY)		sizeMaxY = pSubLandIntv->_cellY;
		}
	}

	printf("minX: %d, maxX: %d, minY: %d, maxY: %d\n", sizeMinX, sizeMaxX, sizeMinY, sizeMaxY);
	sizeX = (sizeMaxX - sizeMinX + 1);
	sizeY = (sizeMaxY - sizeMinY + 1);
	if ((sizeMap = (sizeX * sizeY)) <= 1) {
		return false;
	}

	//  build bitmap
	sizeMap *= SIZE_CELL*SIZE_CELL;
	printf("  building internal bitmap\n");

	unsigned char*	pBmBuffer = new unsigned char[sizeMap*3];

	//  call bitmap fill function
	if (pFillFunction(this, pBmBuffer, sizeMinX, sizeMaxX, sizeMinY, sizeMaxY, sizeX, sizeY, sizeMap)) {
		//  generate bitmap file
		printf("  writing bitmap file\n");

		unsigned char	bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
		unsigned char	bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
		unsigned char	bmppad[3] = {0,0,0};
		int				filesize(54 + 3 * sizeMap);
		int				w       (sizeX * SIZE_CELL);
		int				h       (sizeY * SIZE_CELL);

		bmpfileheader[ 2] = (unsigned char)(filesize    );
		bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
		bmpfileheader[ 4] = (unsigned char)(filesize>>16);
		bmpfileheader[ 5] = (unsigned char)(filesize>>24);

		bmpinfoheader[ 4] = (unsigned char)(       w    );
		bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
		bmpinfoheader[ 6] = (unsigned char)(       w>>16);
		bmpinfoheader[ 7] = (unsigned char)(       w>>24);
		bmpinfoheader[ 8] = (unsigned char)(       h    );
		bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
		bmpinfoheader[10] = (unsigned char)(       h>>16);
		bmpinfoheader[11] = (unsigned char)(       h>>24);

		FILE*	pFile(fopen(fileName.c_str(), "wb"));

		if (pFile != NULL) {
			fwrite(bmpfileheader, 1, 14, pFile);
			fwrite(bmpinfoheader, 1, 40, pFile);

			for (size_t idx(0); idx < sizeMap; ++idx) {
				fwrite(pBmBuffer+(idx*3),   3, 1, pFile);
				if ((idx > 0) && ((idx % w) == 0)) {
					fwrite(bmppad, 1, (4-(w*3)%4)%4, pFile);
				}
			}

			fflush(pFile);
			fclose(pFile);
		}
	}  //  if (filled)

	printf("done\n");
	
	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVclr(unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap)
{
	Tes3SubRecordVNML*		pSubLandVclr(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	size_t					idx         (0);

	memset(pBmBuffer, 0xff, sizeMap * 3 * sizeof (unsigned char));

	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			pSubLandVclr = dynamic_cast<Tes3SubRecordVNML*>(pRecord->findSubRecord("VCLR"));
			if (pSubLandVclr != nullptr) {
				unsigned long	posMapX(pSubLandIntv->_cellX);
				unsigned long	posMapY(pSubLandIntv->_cellY);

				for (short pixY(1); pixY <= SIZE_CELL; ++pixY) {
					for (short pixX(1); pixX <= SIZE_CELL; ++pixX) {
						Tes3SubRecordVNML::BufferEntry&		pixel(pSubLandVclr->_buffer[pixX][pixY]);

						idx           = ((posMapY - sizeMinY) * SIZE_CELL + pixY) * sizeX * SIZE_CELL + ((posMapX - sizeMinX) * SIZE_CELL + pixX);
						if (idx >= sizeMap) {
							fprintf(stderr, "    \x1B[31mover: %d,%d:: %d,%d => %d\033[0m\n", posMapX, posMapY, pixX, pixY, (idx - sizeMap));
							break;
						}
						idx *= 3;
						pBmBuffer[idx]   = pixel._zb;
						pBmBuffer[idx+1] = pixel._yg;
						pBmBuffer[idx+2] = pixel._xr;

					}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgt(unsigned char* pBmBuffer, long sizeMinX, long sizeMaxX, long sizeMinY, long sizeMaxY, size_t sizeX, size_t sizeY, size_t sizeMap)
{
	Tes3SubRecordVHGT*		pSubLandVhgt(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	size_t					idx         (0);

	for (unsigned char *pStart(pBmBuffer), *pEnd(pBmBuffer+sizeMap*3); pStart < pEnd;) {
		*pStart++ = 0x00;
		*pStart++ = 0xFF;
		*pStart++ = 0xFF;
	}
	
	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			pSubLandVhgt = dynamic_cast<Tes3SubRecordVHGT*>(pRecord->findSubRecord("VHGT"));
			if (pSubLandVhgt != nullptr) {
				unsigned long	posMapX   (pSubLandIntv->_cellX);
				unsigned long	posMapY   (pSubLandIntv->_cellY);
				float			offsetCell(pSubLandVhgt->_offset);
				float			offsetRow (0.0);
				float			offsetCol (((signed char) pSubLandVhgt->_height[0][0]));
				int				realHeight(0);

				for (short pixY(0); pixY <= SIZE_CELL; ++pixY) {
					if (pixY > 0) {
						float	value(((signed char) pSubLandVhgt->_height[0][pixY]));

						offsetCol += value;
					}

					offsetRow = offsetCell + offsetCol;

					for (short pixX(0); pixX <= SIZE_CELL; ++pixX) {
						if (pixX > 0) {
							float	value(((signed char) pSubLandVhgt->_height[pixX][pixY]));

							offsetRow += value;
						}

						realHeight = (int) offsetRow;

						if ((pixY > 0) && (pixX > 0)) {
							idx = ((posMapY - sizeMinY) * SIZE_CELL + pixY) * sizeX * SIZE_CELL + ((posMapX - sizeMinX) * SIZE_CELL + pixX);
							if (idx >= sizeMap) {
								fprintf(stderr, "    \x1B[31mover: %d,%d:: %d,%d => %d\033[0m\n", posMapX, posMapY, pixX, pixY, (idx - sizeMap));
								break;
							}
							idx *= 3;
							pBmBuffer[idx]   = (unsigned char) (realHeight >> 0);
							pBmBuffer[idx+1] = (unsigned char) (realHeight >> 8);
							pBmBuffer[idx+2] = (unsigned char) (realHeight >> 16);
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])
	
	return true;
}