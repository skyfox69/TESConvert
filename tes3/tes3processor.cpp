#include "tes3/tes3processor.h"
#include "tes3/subrecord/tes3subrecordintvland.h"
#include "tes3/subrecord/tes3subrecordvnml.h"
#include "tes3/subrecord/tes3subrecordvhgt.h"
#include "tes3/subrecord/tes3subrecordvtex.h"
#include "common/util/tesoptions.h"
#include "common/util/bitmap.h"
#include "common/record/tesrecordmain.h"
#include <cstring>

#define	SIZE_CELL_64	 64
#define	SIZE_CELL_16	 16

//-----------------------------------------------------------------------------
Tes3Processor::Tes3Processor(map<string, vector<TesRecordBase*>>& mapRecords)
	:	Verbosity(),
		_pFillFuncIn(nullptr),
		_mapRecords (mapRecords)
{
	prepareData();
}

//-----------------------------------------------------------------------------
Tes3Processor::~Tes3Processor()
{
	if (_pFillFuncIn != nullptr)	delete _pFillFuncIn;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::prepareData()
{
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);

	if (_pFillFuncIn != nullptr) {
		delete _pFillFuncIn;
		_pFillFuncIn = nullptr;
	}
	_pFillFuncIn = new TesFillFuncIn({999999, -999999, 999999, -999999, 0, 0});

	//  get size of map
	verbose0("preparing data:\n  getting sizes: ");
	for (auto pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if ((pSubLandIntv != nullptr) && (pRecord->findSubRecord("VNML") != nullptr)) {
			if (pSubLandIntv->_cellX < _pFillFuncIn->_sizeMinX)		_pFillFuncIn->_sizeMinX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellX > _pFillFuncIn->_sizeMaxX)		_pFillFuncIn->_sizeMaxX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellY < _pFillFuncIn->_sizeMinY)		_pFillFuncIn->_sizeMinY = pSubLandIntv->_cellY;
			if (pSubLandIntv->_cellY > _pFillFuncIn->_sizeMaxY)		_pFillFuncIn->_sizeMaxY = pSubLandIntv->_cellY;
		}
	}

	verbose0("  minX: %d, maxX: %d, minY: %d, maxY: %d", _pFillFuncIn->_sizeMinX, _pFillFuncIn->_sizeMaxX, _pFillFuncIn->_sizeMinY, _pFillFuncIn->_sizeMaxY);
	_pFillFuncIn->_sizeX = (_pFillFuncIn->_sizeMaxX - _pFillFuncIn->_sizeMinX + 2);
	_pFillFuncIn->_sizeY = (_pFillFuncIn->_sizeMaxY - _pFillFuncIn->_sizeMinY + 2);

	//  get size of map
	if ((_pFillFuncIn->_sizeX * _pFillFuncIn->_sizeY) <= 1) {
		delete _pFillFuncIn;
		_pFillFuncIn = nullptr;
		return false;
	}
	verbose0("done");

	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpWorldspaces()
{
	printf("There are no worldspaces in TES3 files.\n");
	return true;
}

//-----------------------------------------------------------------------------
Bitmap* Tes3Processor::generateVHGTBitmap()
{
	//  check internal data
	if (_pFillFuncIn == nullptr)		return nullptr;

	verbose0("generating intermediate bitmap");
	Bitmap*		pBitmap(new Bitmap(_pFillFuncIn->_sizeX * SIZE_CELL_64, _pFillFuncIn->_sizeY * SIZE_CELL_64));

	if (!dumpVhgt(pBitmap, _pFillFuncIn)) {
		delete pBitmap;
		return nullptr;
	}
	verbose0("done");

	return pBitmap;
}

//-----------------------------------------------------------------------------
Bitmap* Tes3Processor::generateVCLRBitmap()
{
	//  check internal data
	if (_pFillFuncIn == nullptr)		return nullptr;

	verbose0("generating intermediate bitmap");
	Bitmap*		pBitmap(new Bitmap(_pFillFuncIn->_sizeX * SIZE_CELL_64, _pFillFuncIn->_sizeY * SIZE_CELL_64));

	if (!dumpVclr(pBitmap, _pFillFuncIn)) {
		delete pBitmap;
		return nullptr;
	}
	verbose0("done");

	return pBitmap;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVclrMap(string const fileName)
{
	return dumpToMap(fileName, &Tes3Processor::dumpVclr, SIZE_CELL_64);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgtMap(string const fileName)
{
	return dumpToMap(fileName, &Tes3Processor::dumpVhgt, SIZE_CELL_64);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVtexMap(string const fileName)
{
	return dumpToMap(fileName, &Tes3Processor::dumpVtex, SIZE_CELL_16);
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpToMap(const string fileName, Tes3FillFunction pFillFunction, unsigned short cellSize)
{
	//  check internal data
	if (_pFillFuncIn == nullptr)		return false;

	//  build bitmap
	verbose0("generating bitmap file: %s", fileName.c_str());
	verbose0("  building internal bitmap (%d x %d | %d x %d)", _pFillFuncIn->_sizeX, _pFillFuncIn->_sizeY, _pFillFuncIn->_sizeX*cellSize, _pFillFuncIn->_sizeY*cellSize);

	Bitmap		bitmap(_pFillFuncIn->_sizeX * cellSize, _pFillFuncIn->_sizeY * cellSize);

	//  call bitmap fill function
	if (pFillFunction(this, &bitmap, _pFillFuncIn)) {
		//  generate bitmap file
		verbose0("  writing bitmap file");

		bitmap.write(fileName);
		
	}  //  if (filled)

	verbose0("done");
	
	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVclr(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
{
	Tes3SubRecordVNML*		pSubLandVclr(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);

	//  pre-fill bitmap
	pBitmap->clear(0xffff, 0xffff, 0xffff);

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
						bitMapX = (posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_64 + pixX;
						bitMapY = (posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_64 + pixY;

						if (drawGrid && ((pixX == 1) || (pixY == 1))) {
							(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
						} else if (markPos == coordBuf) {
							(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
						} else {
							Tes3SubRecordVNML::BufferEntry&		pixel(pSubLandVclr->_buffer[pixY][pixX]);

							(*pBitmap)(bitMapX, bitMapY).assign(pixel._xr, pixel._yg, pixel._zb);
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL_64; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL_64; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVhgt(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
{
	Tes3SubRecordVHGT*		pSubLandVhgt(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);

	//  pre-fill bitmap
	pBitmap->clear(0xffff, 0xffff, 0x0000);
	
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

						bitMapX = (posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_64 + pixX;
						bitMapY = (posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_64 + pixY;

						if (drawGrid && ((pixX == 1) || (pixY == 1))) {
							(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
						} else if (markPos == coordBuf) {
							(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
						} else {
							(*pBitmap)(bitMapX, bitMapY).assign((unsigned char) (realHeight >> 16), (unsigned char) (realHeight >> 8), (unsigned char) (realHeight >> 0));
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}

//-----------------------------------------------------------------------------
bool Tes3Processor::dumpVtex(Bitmap* pBitmap, TesFillFuncIn* pFillFuncIn)
{
	Tes3SubRecordVTEX*		pSubLandVtex(nullptr);
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	string					markPos     (TESOptions::getInstance()->_markPos);
	size_t					idx         (0);
	long					bitMapX     (0);
	long					bitMapY     (0);
	char					coordBuf[100] = {0};
	bool					drawGrid    (TESOptions::getInstance()->_drawGrid);

	//  pre-fill bitmap
	pBitmap->clear();

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

						bitMapX = (posMapX - pFillFuncIn->_sizeMinX) * SIZE_CELL_16 + pixX;
						bitMapY = (posMapY - pFillFuncIn->_sizeMinY) * SIZE_CELL_16 + pixY;

						if (drawGrid && ((pixX == 1) || (pixY == 1))) {
							(*pBitmap)(bitMapX, bitMapY).assign(0x00, 0x00, 0x00);
						} else if (markPos == coordBuf) {
							(*pBitmap)(bitMapX, bitMapY).assign(0xff, 0x00, 0xff);
						} else {
							(*pBitmap)(bitMapX, bitMapY).assign((unsigned char) (((texIdx & 0x00007C00) >> 8) << 1), (unsigned char) (((texIdx & 0x000003E0) >> 4) << 2), (unsigned char) (((texIdx & 0x0000001F) >> 0) << 3));
						}
					}  //  for (short pixX(0); pixX < SIZE_CELL; ++pixX)
				}  //  for (short pixY(0); pixY < SIZE_CELL; ++pixY)
			}  //  if (pSubLandVclr != nullptr)
		}  //  if (pSubLandIntv != nullptr)
	}  //  for (auto pRecord : _mapRecords["LAND"])

	return true;
}
