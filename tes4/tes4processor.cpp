#include "tes4/tes4processor.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/record/tes4recordgroup.h"
#include "tes4/subrecord/tes4subrecordxclccell.h"
#include "tes4/subrecord/tes4subrecordvnml.h"
#include "tes4/subrecord/tes4subrecordvhgt.h"
#include "common/util/tesoptions.h"
#include "common/util/bitmap.h"
#include "subrecord/tes4subrecordatxt.h"
#include "subrecord/tes4subrecordvtxt.h"
#include "subrecord/tes4subrecordsinglestring.h"
#include <cstring>
#include <sstream>
#include <climits>

#define	SIZE_MAP_MAX	100
#define	SIZE_CELL_64	 64
#define	SIZE_CELL_32	 32
#define	SIZE_CELL_34	 34
#define	SIZE_CELL_16	 16

//-----------------------------------------------------------------------------
Tes4Processor::Tes4Processor(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records)
	:	Verbosity(),
		_mapRecords(mapRecords),
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
	Tes4RecordGroup*	pGroup(nullptr);

	//  pre-fetch CELL records
	for (auto& pRecord : _mapRecords["CELL"]) {
		_mapRecordsCell[((Tes4RecordGeneric*) pRecord)->_id] = (Tes4RecordGeneric*) pRecord;
	}

	//  pre-fetch WRLD and CELL Children groups
	for (auto& pRecord : _mapRecords["GRUP"]) {
		pGroup = dynamic_cast<Tes4RecordGroup*>(pRecord);
		if (pGroup != nullptr) {
			switch (pGroup->_groupType) {
				case 1:		//  WRLD Children
					_mapRecordsGrpWrld[pGroup->_labelL] = pGroup;
					break;
				case 9:		//  external CELL Children
					_mapRecordsGrpCell[pGroup->_labelL] = pGroup;
					break;
			}
		}
	}

	verbose1("  found: %d CELLs, %d WRLD-Groups, %d externel CELL-Groups", _mapRecordsCell.size(), _mapRecordsGrpWrld.size(), _mapRecordsGrpCell.size());
	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::prepareDataRecursive(vector<TesRecordBase*>& records, Tes4RecordGroup* pGroup)
{
	Tes4RecordGeneric*	pRecMain (nullptr);
	Tes4RecordGroup*	pRecGroup(nullptr);

	for (auto& pRecord : records) {
		pRecMain = dynamic_cast<Tes4RecordGeneric*>(pRecord);
		if ((pRecMain != nullptr) && (pRecMain->_name == "LAND") && (pGroup != nullptr)) {
			if (_mapRecordsCell.count(pGroup->_labelL) > 0) {
				Tes4SubRecordXCLCCELL*	pRecXCLC(dynamic_cast<Tes4SubRecordXCLCCELL*>(_mapRecordsCell[pGroup->_labelL]->findSubRecord("XCLC")));

				if (pRecXCLC != nullptr) {
					stringstream	tStrm;

					tStrm << pRecXCLC->_x << ";" << pRecXCLC->_y;
					_mapRecordsLand[tStrm.str()] = pRecMain;
				}
			}
		} else {
			pRecGroup = dynamic_cast<Tes4RecordGroup*>(pRecord);
			if (pRecGroup != nullptr) {
				prepareDataRecursive(*pRecGroup, (pRecGroup->_groupType == 9) ? pRecGroup : nullptr);
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpWorldspaces()
{
	Tes4RecordGeneric*			pRecMain(nullptr);
	Tes4SubRecordSingleString*	pRecSub (nullptr);

	fprintf(stderr, "\nKnown Worldspaces:\n");
	for (auto& pRecord : _mapRecords["WRLD"]) {
		pRecMain = dynamic_cast<Tes4RecordGeneric*>(pRecord);
		if (pRecMain != nullptr) {
			for (auto& pSubRecord : *pRecMain) {
				if (pSubRecord->_name == "EDID") {
					pRecSub = dynamic_cast<Tes4SubRecordSingleString*>(pSubRecord);
					if (pRecSub != nullptr) {
						fprintf(stderr, " - %s\n", pRecSub->_text.c_str());
					}
				}
			}
		}
	}
	printf("\n");
	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVclrMap(string const fileName)
{
	return prepareLandMap(fileName, &Tes4Processor::dumpVclr, SIZE_CELL_32);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVhgtMap(string const fileName)
{
	return prepareLandMap(fileName, &Tes4Processor::dumpVhgt, SIZE_CELL_32);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVtexMap(string const fileName)
{
	return prepareLandMap(fileName, &Tes4Processor::dumpVtex, SIZE_CELL_34);
}

//-----------------------------------------------------------------------------
bool Tes4Processor::prepareLandMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize)
{
	Tes4SubRecordSingleString*	pString(nullptr);
	string						worldspace(TESOptions::getInstance()->_worldspace);

	for (auto& pRecWorld : _mapRecords["WRLD"]) {
		pString = dynamic_cast<Tes4SubRecordSingleString*>(pRecWorld->findSubRecord("EDID"));
		if (pString != nullptr) {
			if (!worldspace.empty() && (worldspace != "l") && (strcmp(pString->_text.c_str(), worldspace.c_str()) != 0)) {
				continue;
			}

			_mapRecordsLand.clear();
			prepareDataRecursive(*_mapRecordsGrpWrld[((Tes4RecordGeneric*) pRecWorld)->_id]);
			if (_mapRecordsLand.size() > 0) {
				stringstream	strm;

				strm << fileName << "_" << pString->_text.c_str() << ".bmp";
				dumpToMap(strm.str(), pFillFunction, cellSize);

			}
		}  //  if (pString != nullptr)
	}  //  for (auto& pRecWorld : _mapRecords["WRLD"])

	return true;}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpToMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize)
{
	Tes4SubRecordXCLCCELL*	pSubCellXclc(nullptr);
	Tes4FillFuncIn			fillFuncIn = {999999, -999999, 999999, -999999, 0, 0, SIZE_MAP_MAX * SIZE_MAP_MAX};

	//  get size of map
	verbose0("generating image file: %s\n  getting sizes: ", fileName.c_str());
	for (auto pRecord : _mapRecords["CELL"]) {
		pSubCellXclc = dynamic_cast<Tes4SubRecordXCLCCELL*>(pRecord->findSubRecord("XCLC"));
		if (pSubCellXclc) {
			if (pSubCellXclc->_x < fillFuncIn._sizeMinX)		fillFuncIn._sizeMinX = pSubCellXclc->_x;
			if (pSubCellXclc->_x > fillFuncIn._sizeMaxX)		fillFuncIn._sizeMaxX = pSubCellXclc->_x;
			if (pSubCellXclc->_y < fillFuncIn._sizeMinY)		fillFuncIn._sizeMinY = pSubCellXclc->_y;
			if (pSubCellXclc->_y > fillFuncIn._sizeMaxY)		fillFuncIn._sizeMaxY = pSubCellXclc->_y;
		}
	}

	verbose0("    minX: %d, maxX: %d, minY: %d, maxY: %d", fillFuncIn._sizeMinX, fillFuncIn._sizeMaxX, fillFuncIn._sizeMinY, fillFuncIn._sizeMaxY);
	fillFuncIn._sizeX = (fillFuncIn._sizeMaxX - fillFuncIn._sizeMinX + 2);
	fillFuncIn._sizeY = (fillFuncIn._sizeMaxY - fillFuncIn._sizeMinY + 2);
	if ((fillFuncIn._sizeMap = (fillFuncIn._sizeX * fillFuncIn._sizeY)) <= 1) {
		return false;
	}

	//  build bitmap
	fillFuncIn._sizeMap *= cellSize*cellSize;
	verbose0("  building internal bitmap");

	Bitmap		bitmap(fillFuncIn._sizeX * cellSize, fillFuncIn._sizeY * cellSize);

	//  call bitmap fill function
	if (pFillFunction(this, &bitmap, &fillFuncIn)) {
		//  generate bitmap file
		verbose0("  writing image file");

		bitmap.write(fileName);

	}  //  if (filled)

	verbose0("done");
<<<<<<< HEAD
=======

>>>>>>> 6796507... wip
	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVclr(Bitmap* pBitmap, Tes4FillFuncIn* pFillFuncIn)
{
	Tes4SubRecordVNML*		pSubLandVclr(nullptr);
	char*					pChar       (nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					posMapX     (0);
	long					posMapY     (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};

	verbose0("  parsing vertex colors");

	//  pre-fill bitmap
	pBitmap->clear(0xffff, 0xffff, 0xffff);

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
					bitMapX = (posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_32 + pixX;
					bitMapY = (posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_32 + pixY;

					if (drawGrid && ((pixX == 1) || (pixY == 1))) {
						(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
					} else if (markPos == coordBuf) {
						(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
					} else {
						Tes4SubRecordVNML::BufferEntry&		pixel(pSubLandVclr->_buffer[pixY][pixX]);

						(*pBitmap)(bitMapX, bitMapY).assign(pixel._xr, pixel._yg, pixel._zb);
					}
				}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
			}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
		}  //  if (pSubLandVclr != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVhgt(Bitmap* pBitmap, Tes4FillFuncIn* pFillFuncIn)
{
	Tes4SubRecordVHGT*		pSubLandVhgt(nullptr);
	char*					pChar       (nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					posMapX     (0);
	long					posMapY     (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	int						heightMin   (INT_MAX);
	int						heightMax   (INT_MIN);
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};

	verbose0("  parsing vertex heights");

	//  pre-fill bitmap
	pBitmap->clear(0xffff, 0xffff, 0x0000);

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
					if (realHeight > heightMax)		heightMax = realHeight;
					if (realHeight < heightMin)		heightMin = realHeight;

					bitMapX = (posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_32 + pixX;
					bitMapY = (posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_32 + pixY;

					if (drawGrid && ((pixX == 1) || (pixY == 1))) {
						(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
					} else if (markPos == coordBuf) {
						(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
					} else {
						(*pBitmap)(bitMapX, bitMapY).assign((unsigned char) (realHeight >> 16), (unsigned char) (realHeight >> 8), (unsigned char) (realHeight >> 0));
					}
				}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
			}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
		}  //  if (pSubLandVhgt != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	verbose1("  min. height: %d, max. height: %d", heightMin, heightMax);
	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVtex(Bitmap* pBitmap, Tes4FillFuncIn* pFillFuncIn)
{
	char*					pChar       (nullptr);
	map<unsigned long, int>	mapTextIds;
	string					markPos     (TESOptions::getInstance()->_markPos);
	long					posMapX     (0);
	long					posMapY     (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	unsigned long			textureId   (0);
	unsigned long			idx         (0);
	unsigned long			offPosX     (0);
	unsigned long			offPosY     (0);
	unsigned long			pixX        (0);
	unsigned long			pixY        (0);
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);
	unsigned char			quadrant    (0);
	char					cBuffer[1000] = {0};
	char					coordBuf[100] = {0};

	verbose0("  parsing textures");

	//  pre-fill bitmap
	pBitmap->clear();

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
				offPosY   = (quadrant / 2) * 17 + posMapY * SIZE_CELL_34;
				mapTextIds[textureId] += 1;
			} else if (pSubRecord->_name == "VTXT") {
				Tes4SubRecordVTXT*	pVtxt((Tes4SubRecordVTXT*) pSubRecord);

				for (unsigned long i(0); i < pVtxt->_count; ++i) {
					pixX = pVtxt->_pEntries[i]._position % 17;
					pixY = pVtxt->_pEntries[i]._position / 17;

					bitMapX = offPosX + pixX - (pFillFuncIn->_sizeMinX * SIZE_CELL_34);
					bitMapY = offPosY + pixY - (pFillFuncIn->_sizeMinX * SIZE_CELL_34);

					if (drawGrid && ((pixX == 1) || (pixY == 1))) {
						(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
					} else if (markPos == coordBuf) {
						(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
					} else {
						(*pBitmap)(bitMapX, bitMapY).assign((unsigned char) (textureId >> 16), (unsigned char) (textureId >> 8), (unsigned char) (textureId >> 0));
					}
				}  //  for (unsigned long i(0); i < pVtxt->_count; ++i)
			}  //  else if (pSubRecord->_name == "VTXT")
		}  //  for (auto& pSubRecord : *entry.second)
	}  //  for (auto entry : _mapRecordsLand)

	verbose1("  found %d unique textures", mapTextIds.size());
	return true;
}
