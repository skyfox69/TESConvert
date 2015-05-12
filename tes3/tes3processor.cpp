#include "tes3/tes3processor.h"
#include "tes3/subrecord/tes3subrecordintvland.h"
#include "tes3/subrecord/tes3subrecordvnml.h"
#include "tes3/subrecord/tes3subrecordvhgt.h"
#include "tes3/subrecord/tes3subrecordvtex.h"
#include "common/util/tesoptions.h"
#include "common/record/tesrecordmain.h"
#include <cstring>

#define	SIZE_MAP_MAX	100
#define	SIZE_CELL_64	 64
#define	SIZE_CELL_16	 16

//-----------------------------------------------------------------------------
Tes3Processor::Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords)
	:	_mapRecords(mapRecords)
{
	prepareData();
}

//-----------------------------------------------------------------------------
Tes3Processor::~Tes3Processor()
{}

//-----------------------------------------------------------------------------
bool Tes3Processor::prepareData()
{
	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVclrMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes3Processor::dumpVclr, SIZE_CELL_64);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgtMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes3Processor::dumpVhgt, SIZE_CELL_64);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVtexMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes3Processor::dumpVtex, SIZE_CELL_16);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpToMap(const string fileName, Tes3FillFunction pFillFunction, unsigned short cellSize)
{
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	Tes3FillFuncIn			fillFuncIn = {999999, -999999, 999999, -999999, 0, 0, SIZE_MAP_MAX * SIZE_MAP_MAX};

	//  get size of map
	printf("generating bitmap file: %s\n  getting sizes: ", fileName.c_str());
	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if ((pSubLandIntv != nullptr) && (pRecord->findSubRecord("VNML") != nullptr)) {
			if (pSubLandIntv->_cellX < fillFuncIn._sizeMinX)		fillFuncIn._sizeMinX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellX > fillFuncIn._sizeMaxX)		fillFuncIn._sizeMaxX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellY < fillFuncIn._sizeMinY)		fillFuncIn._sizeMinY = pSubLandIntv->_cellY;
			if (pSubLandIntv->_cellY > fillFuncIn._sizeMaxY)		fillFuncIn._sizeMaxY = pSubLandIntv->_cellY;
		}
	}

	printf("minX: %d, maxX: %d, minY: %d, maxY: %d\n", fillFuncIn._sizeMinX, fillFuncIn._sizeMaxX, fillFuncIn._sizeMinY, fillFuncIn._sizeMaxY);
	fillFuncIn._sizeX = (fillFuncIn._sizeMaxX - fillFuncIn._sizeMinX + 1);
	fillFuncIn._sizeY = (fillFuncIn._sizeMaxY - fillFuncIn._sizeMinY + 1);
	if ((fillFuncIn._sizeMap = (fillFuncIn._sizeX * fillFuncIn._sizeY)) <= 1) {
		return false;
	}

	//  build bitmap
	fillFuncIn._sizeMap *= cellSize*cellSize;
	printf("  building internal bitmap\n");

	unsigned char*	pBmBuffer = new unsigned char[fillFuncIn._sizeMap*3];

	//  call bitmap fill function
	if (pFillFunction(this, pBmBuffer, &fillFuncIn)) {
		//  generate bitmap file
		printf("  writing bitmap file\n");

		unsigned char	bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
		unsigned char	bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
		unsigned char	bmppad[3] = {0,0,0};
		int				filesize(54 + 3 * fillFuncIn._sizeMap);
		int				w       (fillFuncIn._sizeX * cellSize);
		int				h       (fillFuncIn._sizeY * cellSize);

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

			for (size_t idx(0); idx < fillFuncIn._sizeMap; ++idx) {
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
bool Tes3Processor::dumpVclr(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn)
{
	Tes3SubRecordVNML*		pSubLandVclr(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	bool					verbose     (TESOptions::getInstance()->_verbose);

	memset(pBmBuffer, 0xff, pFillFuncIn->_sizeMap * 3 * sizeof (unsigned char));

	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			pSubLandVclr = dynamic_cast<Tes3SubRecordVNML*>(pRecord->findSubRecord("VCLR"));
			if (pSubLandVclr != nullptr) {
				long	posMapX(pSubLandIntv->_cellX);
				long	posMapY(pSubLandIntv->_cellY);

				if ((posMapX < pFillFuncIn->_sizeMinX) || (posMapX > pFillFuncIn->_sizeMaxX) ||
					(posMapY < pFillFuncIn->_sizeMinY) || (posMapY > pFillFuncIn->_sizeMaxY)) {
					continue;
				}

				sprintf(coordBuf, "%d,%d", posMapX, posMapY);

				for (short pixY(1); pixY <= SIZE_CELL_64; ++pixY) {
					for (short pixX(1); pixX <= SIZE_CELL_64; ++pixX) {
						Tes3SubRecordVNML::BufferEntry&		pixel(pSubLandVclr->_buffer[pixY][pixX]);

						idx = ((posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_64 + pixY) * pFillFuncIn->_sizeX * SIZE_CELL_64 + ((posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_64 + pixX);
						if (idx >= pFillFuncIn->_sizeMap) {
							if (verbose)	fprintf(stderr, "    \x1B[31mover: %d,%d:: %d,%d => %d\033[0m\n", posMapX, posMapY, pixX, pixY, (idx - pFillFuncIn->_sizeMap));
							break;
						}
						idx *= 3;

						if (drawGrid && ((pixX == 1) || (pixY == 1))) {
							pBmBuffer[idx]   = 0;
							pBmBuffer[idx+1] = 0;
							pBmBuffer[idx+2] = 0;
						} else if (markPos == coordBuf) {
							pBmBuffer[idx]   = 0xff;
							pBmBuffer[idx+1] = 0x00;
							pBmBuffer[idx+2] = 0xff;
						} else {
							pBmBuffer[idx]   = pixel._zb;
							pBmBuffer[idx+1] = pixel._yg;
							pBmBuffer[idx+2] = pixel._xr;
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL_64; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL_64; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgt(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn)
{
	Tes3SubRecordVHGT*		pSubLandVhgt(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	bool					verbose     (TESOptions::getInstance()->_verbose);

	for (unsigned char *pStart(pBmBuffer), *pEnd(pBmBuffer+pFillFuncIn->_sizeMap*3); pStart < pEnd;) {
		*pStart++ = 0x00;
		*pStart++ = 0xFF;
		*pStart++ = 0xFF;
	}
	
	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			pSubLandVhgt = dynamic_cast<Tes3SubRecordVHGT*>(pRecord->findSubRecord("VHGT"));
			if (pSubLandVhgt != nullptr) {
				long			posMapX   (pSubLandIntv->_cellX);
				long			posMapY   (pSubLandIntv->_cellY);
				float			offsetCell(pSubLandVhgt->_offset);
				float			offsetRow (0.0);
				float			offsetCol (((signed char) pSubLandVhgt->_height[0][0]));
				int				realHeight(0);

				if ((posMapX < pFillFuncIn->_sizeMinX) || (posMapX > pFillFuncIn->_sizeMaxX) ||
					(posMapY < pFillFuncIn->_sizeMinY) || (posMapY > pFillFuncIn->_sizeMaxY)) {
					continue;
				}

				sprintf(coordBuf, "%d,%d", posMapX, posMapY);

				for (short pixY(0); pixY <= SIZE_CELL_64; ++pixY) {
					if (pixY > 0) {
						float	value(((signed char) pSubLandVhgt->_height[pixY][0]));

						offsetCol += value;
					}

					offsetRow = offsetCell + offsetCol;

					for (short pixX(0); pixX <= SIZE_CELL_64; ++pixX) {
						if (pixX > 0) {
							float	value(((signed char) pSubLandVhgt->_height[pixY][pixX]));

							offsetRow += value;
						}

						realHeight = (int) offsetRow;

						idx = ((posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_64 + pixY) * pFillFuncIn->_sizeX * SIZE_CELL_64 + ((posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_64 + pixX);
						if (idx >= pFillFuncIn->_sizeMap) {
							if (verbose)	fprintf(stderr, "    \x1B[31mover: %d,%d:: %d,%d => %d\033[0m\n", posMapX, posMapY, pixX, pixY, (idx - pFillFuncIn->_sizeMap));
							break;
						}
						idx *= 3;

						if (drawGrid && ((pixX == 1) || (pixY == 1))) {
							pBmBuffer[idx]   = 0;
							pBmBuffer[idx+1] = 0;
							pBmBuffer[idx+2] = 0;
						} else if (markPos == coordBuf) {
							pBmBuffer[idx]   = 0xff;
							pBmBuffer[idx+1] = 0x00;
							pBmBuffer[idx+2] = 0xff;
						} else if ((pixY > 0) && (pixX > 0)) {
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

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVtex(unsigned char* pBmBuffer, Tes3FillFuncIn* pFillFuncIn)
{
#if 0
	Tes3SubRecordSingleULong*		pSubLtexINTV(nullptr);
	Tes3SubRecordSingleString*		pSubLtexNAME(nullptr);
	map<unsigned long, string>		mapTextures;

	//  build texture lookup map (not needed anyway)
	for (auto& pRecord : _mapRecords["LTEX"]) {
		pSubLtexINTV = dynamic_cast<Tes3SubRecordSingleULong*>(pRecord->findSubRecord("INTV"));
		pSubLtexNAME = dynamic_cast<Tes3SubRecordSingleString*>(pRecord->findSubRecord("NAME"));
		if ((pSubLtexINTV != nullptr) && (pSubLtexNAME != nullptr)) {
			mapTextures[pSubLtexINTV->_value] = pSubLtexNAME->_text;
		}
	}
#endif
	Tes3SubRecordVTEX*		pSubLandVtex(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	bool					verbose     (TESOptions::getInstance()->_verbose);

	memset(pBmBuffer, 0x00, pFillFuncIn->_sizeMap * 3 * sizeof (unsigned char));

	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			pSubLandVtex = dynamic_cast<Tes3SubRecordVTEX*>(pRecord->findSubRecord("VTEX"));
			if (pSubLandVtex != nullptr) {
				long	posMapX(pSubLandIntv->_cellX);
				long	posMapY(pSubLandIntv->_cellY);

				if ((posMapX < pFillFuncIn->_sizeMinX) || (posMapX > pFillFuncIn->_sizeMaxX) ||
					(posMapY < pFillFuncIn->_sizeMinY) || (posMapY > pFillFuncIn->_sizeMaxY)) {
					continue;
				}

				sprintf(coordBuf, "%d,%d", posMapX, posMapY);

				for (short pixY(0); pixY < SIZE_CELL_16; ++pixY) {
					for (short pixX(0); pixX < SIZE_CELL_16; ++pixX) {
						unsigned short	texIdx = pSubLandVtex->_texStd[pixY][pixX];

						idx = ((posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_16 + pixY) * pFillFuncIn->_sizeX * SIZE_CELL_16 + ((posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_16 + pixX);
						if (idx >= pFillFuncIn->_sizeMap) {
							if (verbose)	fprintf(stderr, "    \x1B[31mover: %d,%d:: %d,%d => %d\033[0m\n", posMapX, posMapY, pixX, pixY, (idx - pFillFuncIn->_sizeMap));
							break;
						}
						idx *= 3;

						if (drawGrid && ((pixX == 0) || (pixY == 0))) {
							pBmBuffer[idx]   = 0xff;
							pBmBuffer[idx+1] = 0;
							pBmBuffer[idx+2] = 0;
						} else if (markPos == coordBuf) {
							pBmBuffer[idx]   = 0xff;
							pBmBuffer[idx+1] = 0x00;
							pBmBuffer[idx+2] = 0xff;
						} else {
							pBmBuffer[idx]   = (unsigned char) (((texIdx & 0x0000001F) >> 0) << 3);
							pBmBuffer[idx+1] = (unsigned char) (((texIdx & 0x000003E0) >> 4) << 2);
							pBmBuffer[idx+2] = (unsigned char) (((texIdx & 0x00007C00) >> 8) << 1);
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}
