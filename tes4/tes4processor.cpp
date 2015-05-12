#include "tes4/tes4processor.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/record/tes4recordgroup.h"
#include "tes4/subrecord/tes4subrecordxclccell.h"
#include "tes4/subrecord/tes4subrecordvnml.h"
#include "tes4/subrecord/tes4subrecordvhgt.h"
#include "common/util/tesoptions.h"
#include "subrecord/tes4subrecordatxt.h"
#include "subrecord/tes4subrecordvtxt.h"
#include <cstring>
#include <sstream>

#define	SIZE_MAP_MAX	100
#define	SIZE_CELL_64	 64
#define	SIZE_CELL_32	 32
#define	SIZE_CELL_34	 34
#define	SIZE_CELL_16	 16

//-----------------------------------------------------------------------------
Tes4Processor::Tes4Processor(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records)
	:	_mapRecords(mapRecords),
		_records   (records)
{
	prepareData();
}

//-----------------------------------------------------------------------------
Tes4Processor::~Tes4Processor()
{}

//-----------------------------------------------------------------------------
bool Tes4Processor::prepareData()
{
	map<unsigned long, Tes4RecordGeneric*>	mapRecordIds;

	for (auto& pRecord : _mapRecords["CELL"]) {
		mapRecordIds[((Tes4RecordGeneric*) pRecord)->_id] = (Tes4RecordGeneric*) pRecord;
	}

	prepareDataRecursive(_records, mapRecordIds);

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::prepareDataRecursive(vector<TesRecordBase*>& records, map<unsigned long, Tes4RecordGeneric*>& mapRecordIds, Tes4RecordGroup* pGroup)
{
	Tes4RecordGeneric*	pRecMain (nullptr);
	Tes4RecordGroup*	pRecGroup(nullptr);

	for (auto& pRecord : records) {
		pRecMain = dynamic_cast<Tes4RecordGeneric*>(pRecord);
		if ((pRecMain != nullptr) && (pRecMain->_name == "LAND") && (pGroup != nullptr)) {
			if (mapRecordIds.count(pGroup->_labelL) > 0) {
				Tes4SubRecordXCLCCELL*	pRecXCLC(dynamic_cast<Tes4SubRecordXCLCCELL*>(mapRecordIds[pGroup->_labelL]->findSubRecord("XCLC")));

				if (pRecXCLC != nullptr) {
					stringstream	tStrm;

					tStrm << pRecXCLC->_x << ";" << pRecXCLC->_y;
					_mapRecordsLand[tStrm.str()] = pRecMain;
				}
			}
		} else {
			pRecGroup = dynamic_cast<Tes4RecordGroup*>(pRecord);
			if (pRecGroup != nullptr) {
				prepareDataRecursive(*pRecGroup, mapRecordIds, (pRecGroup->_groupType == 9) ? pRecGroup : nullptr);
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVclrMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes4Processor::dumpVclr, SIZE_CELL_32);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVhgtMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes4Processor::dumpVhgt, SIZE_CELL_32);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVtexMap(string const fileName)
{
	return dumpToMap(fileName + ".bmp", &Tes4Processor::dumpVtex, SIZE_CELL_34);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpToMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize)
{
	Tes4SubRecordXCLCCELL*	pSubCellXclc(nullptr);
	Tes4FillFuncIn			fillFuncIn = {999999, -999999, 999999, -999999, 0, 0, SIZE_MAP_MAX * SIZE_MAP_MAX};

	//  get size of map
	printf("generating bitmap file: %s\n  getting sizes: ", fileName.c_str());
	for (auto pRecord : _mapRecords["CELL"]) {
		pSubCellXclc = dynamic_cast<Tes4SubRecordXCLCCELL*>(pRecord->findSubRecord("XCLC"));
		if (pSubCellXclc) {
			if (pSubCellXclc->_x < fillFuncIn._sizeMinX)		fillFuncIn._sizeMinX = pSubCellXclc->_x;
			if (pSubCellXclc->_x > fillFuncIn._sizeMaxX)		fillFuncIn._sizeMaxX = pSubCellXclc->_x;
			if (pSubCellXclc->_y < fillFuncIn._sizeMinY)		fillFuncIn._sizeMinY = pSubCellXclc->_y;
			if (pSubCellXclc->_y > fillFuncIn._sizeMaxY)		fillFuncIn._sizeMaxY = pSubCellXclc->_y;
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
bool Tes4Processor::dumpVclr(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn)
{
	Tes4SubRecordVNML*		pSubLandVclr(nullptr);
	char*					pChar       (nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					posMapX     (0);
	long					posMapY     (0);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	bool					verbose     (TESOptions::getInstance()->_verbose);

	memset(pBmBuffer, 0xff, pFillFuncIn->_sizeMap * 3 * sizeof (unsigned char));

	for (auto entry : _mapRecordsLand) {
		pSubLandVclr = dynamic_cast<Tes4SubRecordVNML*>(entry.second->findSubRecord("VCLR"));
		if (pSubLandVclr != nullptr) {
			strncpy(cBuffer, entry.first.c_str(), 1000);
			pChar = strchr(cBuffer, ';');
			posMapX = atol(cBuffer);
			posMapY = atol(++pChar);

			if ((posMapX < pFillFuncIn->_sizeMinX) || (posMapX > pFillFuncIn->_sizeMaxX) ||
				(posMapY < pFillFuncIn->_sizeMinY) || (posMapY > pFillFuncIn->_sizeMaxY)) {
				continue;
			}

			sprintf(coordBuf, "%d,%d", posMapX, posMapY);

			for (short pixY(1); pixY <= SIZE_CELL_32; ++pixY) {
				for (short pixX(1); pixX <= SIZE_CELL_32; ++pixX) {
					Tes4SubRecordVNML::BufferEntry&		pixel(pSubLandVclr->_buffer[pixY][pixX]);

					idx           = ((posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_32 + pixY) * pFillFuncIn->_sizeX * SIZE_CELL_32 + ((posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_32 + pixX);
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
				}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
			}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
		}  //  if (pSubLandVclr != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVhgt(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn)
{
	Tes4SubRecordVHGT*		pSubLandVhgt(nullptr);
	char*					pChar       (nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					posMapX     (0);
	long					posMapY     (0);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	bool					verbose     (TESOptions::getInstance()->_verbose);

	for (unsigned char *pStart(pBmBuffer), *pEnd(pBmBuffer+pFillFuncIn->_sizeMap*3); pStart < pEnd;) {
		*pStart++ = 0x00;
		*pStart++ = 0xFF;
		*pStart++ = 0xFF;
	}

	for (auto entry : _mapRecordsLand) {
		pSubLandVhgt = dynamic_cast<Tes4SubRecordVHGT*>(entry.second->findSubRecord("VHGT"));
		if (pSubLandVhgt != nullptr) {
			strncpy(cBuffer, entry.first.c_str(), 1000);
			pChar = strchr(cBuffer, ';');
			posMapX = atol(cBuffer);
			posMapY = atol(++pChar);

			if ((posMapX < pFillFuncIn->_sizeMinX) || (posMapX > pFillFuncIn->_sizeMaxX) ||
				(posMapY < pFillFuncIn->_sizeMinY) || (posMapY > pFillFuncIn->_sizeMaxY)) {
				continue;
			}

			sprintf(coordBuf, "%d,%d", posMapX, posMapY);

			float	offsetCell(pSubLandVhgt->_offset);
			float	offsetRow (0.0);
			float	offsetCol (((signed char) pSubLandVhgt->_height[0][0]));
			int		realHeight(0);

			for (short pixY(0); pixY <= SIZE_CELL_32; ++pixY) {
				if (pixY > 0) {
					float	value(((signed char) pSubLandVhgt->_height[pixY][0]));

					offsetCol += value;
				}

				offsetRow = offsetCell + offsetCol;

				for (short pixX(0); pixX <= SIZE_CELL_32; ++pixX) {
					if (pixX > 0) {
						float	value(((signed char) pSubLandVhgt->_height[pixY][pixX]));

						offsetRow += value;
					}

					realHeight = (int) offsetRow;

					idx = ((posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_32 + pixY) * pFillFuncIn->_sizeX * SIZE_CELL_32 + ((posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_32 + pixX);
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
		}  //  if (pSubLandVhgt != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVtex(unsigned char* pBmBuffer, Tes4FillFuncIn* pFillFuncIn)
{
	char*					pChar       (nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	long					posMapX     (0);
	long					posMapY     (0);
	unsigned long			textureId   (0);
	unsigned long			idx         (0);
	unsigned long			offPosX     (0);
	unsigned long			offPosY     (0);
	unsigned long			pixX        (0);
	unsigned long			pixY        (0);
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	unsigned char	quadrant            (0);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};

	memset(pBmBuffer, 0x00, pFillFuncIn->_sizeMap * 3 * sizeof (unsigned char));

	for (auto entry : _mapRecordsLand) {
		strncpy(cBuffer, entry.first.c_str(), 1000);
		pChar = strchr(cBuffer, ';');
		posMapX = atol(cBuffer);
		posMapY = atol(++pChar);

		sprintf(coordBuf, "%d,%d", posMapX, posMapY);

		for (auto& pSubRecord : *entry.second) {
			if (pSubRecord->_name == "ATXT") {
				quadrant  = ((Tes4SubRecordATXT*) pSubRecord)->_quadrant;
				textureId = ((Tes4SubRecordATXT*) pSubRecord)->_textureId;
				offPosX   = (quadrant % 2) * 17 + posMapX * SIZE_CELL_34;
				offPosY   = (quadrant / 2) * pFillFuncIn->_sizeX * SIZE_CELL_34 * 17 + posMapY * pFillFuncIn->_sizeX * SIZE_CELL_34 * SIZE_CELL_34;
			} else if (pSubRecord->_name == "VTXT") {
				Tes4SubRecordVTXT*	pVtxt((Tes4SubRecordVTXT*) pSubRecord);

				for (unsigned long i(0); i < pVtxt->_count; ++i) {
					pixX = pVtxt->_pEntries[i]._position % 17;
					pixY = pVtxt->_pEntries[i]._position / 17;

					idx = (offPosY + pixY * pFillFuncIn->_sizeX * SIZE_CELL_34) + (offPosX + pixX);
					idx *= 3;

					if (drawGrid && ((pixX == 0) || (pixY == 0))) {
						pBmBuffer[idx]   = 0x00;
						pBmBuffer[idx+1] = 0x00;
						pBmBuffer[idx+2] = 0x00;
					} else if (markPos == coordBuf) {
						pBmBuffer[idx]   = 0xff;
						pBmBuffer[idx+1] = 0x00;
						pBmBuffer[idx+2] = 0xff;
					} else {
						pBmBuffer[idx]   = (unsigned char) (textureId >> 0);
						pBmBuffer[idx+1] = (unsigned char) (textureId >> 8);
						pBmBuffer[idx+2] = (unsigned char) (textureId >> 16);
					}
				}  //  for (unsigned long i(0); i < pVtxt->_count; ++i)
			}  //  else if (pSubRecord->_name == "VTXT")
		}  //  for (auto& pSubRecord : *entry.second)
	}  //  for (auto entry : _mapRecordsLand)
	
	return true;
}
