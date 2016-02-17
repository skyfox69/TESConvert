#include "tes4/tes4processor.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/record/tes4recordgroup.h"
#include "tes4/subrecord/tes4subrecordxclccell.h"
#include "tes4/subrecord/tes4subrecordvnml.h"
#include "tes4/subrecord/tes4subrecordvhgt.h"
#include "common/util/tesoptions.h"
#include "common/util/bitmap.h"
#include "subrecord/tes4subrecordatxt.h"
#include "subrecord/tes4subrecordbtxt.h"
#include "subrecord/tes4subrecordvtxt.h"
#include "subrecord/tes4subrecordsinglestring.h"
#include <cstring>
#include <sstream>
#include <climits>

#define	SIZE_CELL_64	 64
#define	SIZE_CELL_32	 32
#define	SIZE_CELL_34	 34
#define	SIZE_CELL_16	 16

//-----------------------------------------------------------------------------
Tes4Processor::Tes4Processor(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records)
	:	Verbosity(),
		_pFillFuncIn(nullptr),
		_mapRecords (mapRecords),
		_records    (records)
{
	prepareData();
}

//-----------------------------------------------------------------------------
Tes4Processor::~Tes4Processor()
{
	if (_pFillFuncIn != nullptr)		delete _pFillFuncIn;
}

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
	Tes4RecordGeneric*		pRecMain (nullptr);
	Tes4RecordGroup*		pRecGroup(nullptr);
	Tes4SubRecordXCLCCELL*	pRecXCLC (nullptr);

	for (auto& pRecord : records) {
		pRecMain = dynamic_cast<Tes4RecordGeneric*>(pRecord);
		if ((pRecMain != nullptr) && (pRecMain->_name == "LAND") && (pGroup != nullptr)) {
			if (_mapRecordsCell.count(pGroup->_labelL) > 0) {
				pRecXCLC = dynamic_cast<Tes4SubRecordXCLCCELL*>(_mapRecordsCell[pGroup->_labelL]->findSubRecord("XCLC"));

				if (pRecXCLC != nullptr) {
					stringstream	tStrm;

					tStrm << pRecXCLC->_x << ";" << pRecXCLC->_y;
					_mapRecordsLand[tStrm.str()] = pRecMain;

					//  get map limits
					if (pRecXCLC->_x < _pFillFuncIn->_sizeMinX)		_pFillFuncIn->_sizeMinX = pRecXCLC->_x;
					if (pRecXCLC->_x > _pFillFuncIn->_sizeMaxX)		_pFillFuncIn->_sizeMaxX = pRecXCLC->_x;
					if (pRecXCLC->_y < _pFillFuncIn->_sizeMinY)		_pFillFuncIn->_sizeMinY = pRecXCLC->_y;
					if (pRecXCLC->_y > _pFillFuncIn->_sizeMaxY)		_pFillFuncIn->_sizeMaxY = pRecXCLC->_y;
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
Bitmap* Tes4Processor::generateVHGTBitmap()
{
	return nullptr;
}

//-----------------------------------------------------------------------------
Bitmap* Tes4Processor::generateVCLRBitmap()
{
	return nullptr;
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

			if (_pFillFuncIn != nullptr) {
				delete _pFillFuncIn;
				_pFillFuncIn = nullptr;
			}
			_pFillFuncIn = new TesFillFuncIn({999999, -999999, 999999, -999999, 0, 0});
			_mapRecordsLand.clear();
			prepareDataRecursive(*_mapRecordsGrpWrld[((Tes4RecordGeneric*) pRecWorld)->_id]);
			if (_mapRecordsLand.size() > 0) {
				stringstream	strm;

				strm << fileName << "_" << pString->_text.c_str();
				dumpToMap(strm.str(), pFillFunction, cellSize);

			}
		}  //  if (pString != nullptr)
	}  //  for (auto& pRecWorld : _mapRecords["WRLD"])

	return true;}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpToMap(const string fileName, Tes4FillFunction pFillFunction, unsigned short cellSize)
{
	//  get size of map
	verbose0("generating image file: %s\n  getting sizes: ", fileName.c_str());
	verbose0("    minX: %d, maxX: %d, minY: %d, maxY: %d", _pFillFuncIn->_sizeMinX, _pFillFuncIn->_sizeMaxX, _pFillFuncIn->_sizeMinY, _pFillFuncIn->_sizeMaxY);
	_pFillFuncIn->_sizeX = (_pFillFuncIn->_sizeMaxX - _pFillFuncIn->_sizeMinX + 2);
	_pFillFuncIn->_sizeY = (_pFillFuncIn->_sizeMaxY - _pFillFuncIn->_sizeMinY + 2);
	if ((_pFillFuncIn->_sizeX * _pFillFuncIn->_sizeY) <= 1) {
		return false;
	}

	//  build bitmap
	verbose0("  building internal bitmap");

	Bitmap		bitmap(_pFillFuncIn->_sizeX * cellSize, _pFillFuncIn->_sizeY * cellSize);

	//  call bitmap fill function
	if (pFillFunction(this, &bitmap, _pFillFuncIn)) {
		//  generate bitmap file
		verbose0("  writing image file");

		bitmap.write(fileName);

	}  //  if (filled)

	verbose0("done");
	return true;
}

//-----------------------------------------------------------------------------
bool Tes4Processor::dumpVclr(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
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
bool Tes4Processor::dumpVhgt(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
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
bool Tes4Processor::dumpVtex(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
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

		unsigned long	textureIds[4][17][17] = {0};
		float			opacities [4][17][17] = {0.0};

		for (auto& pSubRecord : *entry.second) {
			if (pSubRecord->_name == "BTXT") {
				quadrant  = ((Tes4SubRecordBTXT*) pSubRecord)->_quadrant;
				textureId = ((Tes4SubRecordBTXT*) pSubRecord)->_textureId;
				mapTextIds[textureId] += 1;

				for (unsigned short iy(0); iy < 17; ++iy) {
					for (unsigned short ix(0); ix < 17; ++ix) {
						textureIds[quadrant][iy][ix] = textureId;
						opacities [quadrant][iy][ix] = 0.0;
					}
				}
			} else if (pSubRecord->_name == "ATXT") {
				quadrant  = ((Tes4SubRecordATXT*) pSubRecord)->_quadrant;
				textureId = ((Tes4SubRecordATXT*) pSubRecord)->_textureId;
				mapTextIds[textureId] += 1;
			} else if (pSubRecord->_name == "VTXT") {

				Tes4SubRecordVTXT*	pVtxt((Tes4SubRecordVTXT*) pSubRecord);

				for (size_t i(0); i < pVtxt->_count; ++i) {
					pixX = pVtxt->_pEntries[i]._position % 17;
					pixY = pVtxt->_pEntries[i]._position / 17;

					if (opacities[quadrant][pixY][pixX] <= pVtxt->_pEntries[i]._opacity) {
						opacities[quadrant][pixY][pixX] = pVtxt->_pEntries[i]._opacity;
						textureIds[quadrant][pixY][pixX] = textureId;
					}
				}  //  for (unsigned long i(0); i < pVtxt->_count; ++i)
			}  //  } else if (pSubRecord->_name == "VTXT")
		}  //  for (auto& pSubRecord : *entry.second)

		//  write data into bitmap
		for (quadrant=0; quadrant < 4; ++quadrant) {
			offPosX   = (quadrant % 2) * 17 + posMapX * SIZE_CELL_34;
			offPosY   = (quadrant / 2) * 17 + posMapY * SIZE_CELL_34;

			for (unsigned short position(0); position < 289; ++position) {
				pixX = position % 17;
				pixY = position / 17;

				bitMapX = offPosX + pixX - (pFillFuncIn->_sizeMinX * SIZE_CELL_34);
				bitMapY = offPosY + pixY - (pFillFuncIn->_sizeMinY * SIZE_CELL_34);

				if (drawGrid && ((pixX == 1) || (pixY == 1))) {
					(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
				} else if (markPos == coordBuf) {
					(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
				} else {
					textureId = textureIds[quadrant][pixY][pixX];
					(*pBitmap)(bitMapX, bitMapY).assign((unsigned char) (textureId >> 16), (unsigned char) (textureId >> 8), (unsigned char) (textureId >> 0));
				}
			}  //  for (unsigned short position(0), position < 289; ++position)
		}  //  for (quadrant=0; quadrant < 4; ++quadrant)
	}  //  for (auto entry : _mapRecordsLand)

	verbose1("  found %d unique textures", mapTextIds.size());
	return true;
}
