#include "tes4/tes4converter.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/record/tes4recordgroup.h"
#include "tes4/subrecord/tes4subrecordall.h"
#include "common/util/bitmap.h"
#include "common/util/tesoptions.h"
#include "common/util/tesmappingstorage.h"
#include <ctime>
#include <climits>

#define	SIZE_CELL_16			16
#define	SIZE_CELL_32			32
#define	SIZE_CELL_64			64

#define	MAX_CELLS_PER_GROUP5	64
#define	MAX_GROUP5_PER_GROUP4	16

//-----------------------------------------------------------------------------
static	unsigned char	stGRUPWRLD0[24] = {'G','R','U','P', 0,0,0,0, 'W','R','L','D', 0,0,0,0, 4,20, 0,0, 0,0, 0,0};
static	unsigned char	stGRUPWRLD1[24] = {'G','R','U','P', 0,0,0,0, 0,0,0,0, 1,0,0,0, 4,20, 0,0, 0,0, 0,0};
static	unsigned char	stGRUPTYPE4[24] = {'G','R','U','P', 0,0,0,0, 0,0,0,0, 4,0,0,0, 4,20, 0,0, 0,0, 0,0};
static	unsigned char	stGRUPTYPE5[24] = {'G','R','U','P', 0,0,0,0, 0,0,0,0, 5,0,0,0, 4,20, 0,0, 0,0, 0,0};
static	unsigned char	stGRUPTYPE6[24] = {'G','R','U','P', 0,0,0,0, 0,0,0,0, 6,0,0,0, 4,20, 0,0, 0,0, 0,0};
static	unsigned char	stGRUPTYPE9[24] = {'G','R','U','P', 0,0,0,0, 0,0,0,0, 9,0,0,0, 4,20, 0,0, 0,0, 0,0};

//-----------------------------------------------------------------------------
Tes4Converter::Tes4Converter(map<string, vector<TesRecordBase*>>& mapRecords, vector<TesRecordBase*>& records, string const worldspace)
	:	Verbosity(),
		_mapRecords(mapRecords),
		_records   (records),
		_worldspace("TESConvert"),
		_objectId  (0)
{
	//  initialize object id
	time_t		timeAct   (time(NULL));
	struct tm	*pTimeInfo(localtime(&timeAct));

	_objectId = (pTimeInfo->tm_year << 16) + (pTimeInfo->tm_mon << 8) + pTimeInfo->tm_mday;

	//  initialize worldspace
	if (!worldspace.empty() && (worldspace != "l")) {
		_worldspace = worldspace;
	}
}

//-----------------------------------------------------------------------------
Tes4Converter::~Tes4Converter()
{}

//-----------------------------------------------------------------------------
void Tes4Converter::prepareData(Tes4SubRecordMNAM* pSubMNAM)
{
	Tes3SubRecordINTVLAND*	pSubLandIntv(nullptr);
	char					cBuffer[100] = {0};

	//  MNAM
	pSubMNAM->_cellNwX = SHRT_MAX;
	pSubMNAM->_cellNwY = SHRT_MIN;
	pSubMNAM->_cellSeX = SHRT_MIN;
	pSubMNAM->_cellSeY = SHRT_MAX;

	for (auto& pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			if (pSubLandIntv->_cellX < pSubMNAM->_cellNwX)			pSubMNAM->_cellNwX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellY > pSubMNAM->_cellNwY)			pSubMNAM->_cellNwY = pSubLandIntv->_cellY;
			if (pSubLandIntv->_cellX > pSubMNAM->_cellSeX)			pSubMNAM->_cellSeX = pSubLandIntv->_cellX;
			if (pSubLandIntv->_cellY < pSubMNAM->_cellSeY)			pSubMNAM->_cellSeY = pSubLandIntv->_cellY;
		}
	}
	pSubMNAM->_width  = pSubMNAM->_cellSeX - pSubMNAM->_cellNwX + 1;
	pSubMNAM->_height = pSubMNAM->_cellNwY - pSubMNAM->_cellSeY + 1;

	//  LAND by coordinates
	for (auto& pRecord : _mapRecords["LAND"]) {
		pSubLandIntv = dynamic_cast<Tes3SubRecordINTVLAND*>(pRecord->findSubRecord("INTV"));
		if (pSubLandIntv != nullptr) {
			sprintf(cBuffer, "%d;%d", (pSubLandIntv->_cellX - pSubMNAM->_cellNwX), (pSubLandIntv->_cellY - pSubMNAM->_cellSeY));
			_mapRecordsLands[cBuffer] = pRecord;
		}
	}

	//
}

//-----------------------------------------------------------------------------
bool Tes4Converter::convert(string const fileName, Bitmap* pBitmapVHGT, Bitmap* pBitmapVCLR, Bitmap* pBitmapVTEX)
{
	Tes4RecordGeneric*		pWRLD    (new Tes4RecordGeneric("WRLD", _objectId++));
	Tes4RecordGeneric*		pCELL    (nullptr);
	Tes4RecordGeneric*		pLAND    (nullptr);
	Tes4RecordGroup*		pGrpWRLD0(new Tes4RecordGroup(stGRUPWRLD0));
	Tes4RecordGroup*		pGrpWRLD1(new Tes4RecordGroup(stGRUPWRLD1));
	Tes4RecordGroup*		pGrpType4(nullptr);
	Tes4RecordGroup*		pGrpType5(nullptr);
	Tes4RecordGroup*		pGrpType6(nullptr);
	Tes4RecordGroup*		pGrpType9(nullptr);
	Tes4SubRecordHEDR*		pSubHEDR (new Tes4SubRecordHEDR());
	Tes4SubRecordMNAM*		pSubMNAM (new Tes4SubRecordMNAM());
	Tes4SubRecordVHGT*		pSubVHGT (nullptr);
	Tes4SubRecordVNML*		pSubVCLR (nullptr);
	TESOptions*				pOptions (TESOptions::getInstance());
	TESMappingStorage*		pMapStore(TESMappingStorage::getInstance());
	long					posMapX32(0);
	long					posMapY32(0);
	long					posMapX64(0);
	long					posMapY64(0);
	unsigned int			bmpX     (0);
	unsigned int			bmpY     (0);
	unsigned int			cntCELL  (0);
	unsigned int			cntGROUP5(0);
	char					coordBuf[100] = {0};

	//  prepare TES4 Header
	Tes4RecordGeneric		tes4Header("TES4", 0);

	tes4Header.push_back(pSubHEDR);
	tes4Header.push_back(new Tes4SubRecordSingleString("CNAM", "TESConvert"));
	for (auto& master : pOptions->_masterNames) {
		tes4Header.push_back(new Tes4SubRecordSingleString("MAST", master));
	}

	//  prepare group WRLD
	tes4Header.push_back(pGrpWRLD0);
	pSubHEDR->_numRecords++;

	//  prepare WRLD
	prepareData(pSubMNAM);

	pGrpWRLD0->push_back(pWRLD);
	pSubHEDR->_numRecords++;

	pWRLD->push_back(new Tes4SubRecordSingleString("EDID", _worldspace));
	pWRLD->push_back(new Tes4SubRecordSingleString("FULL", _worldspace));
	pWRLD->push_back(new Tes4SubRecordSingleULong("NAM2", 24));
	pWRLD->push_back(pSubMNAM);
	pWRLD->push_back(new Tes4SubRecordSingleUChar("DATA", 0x00));
	pWRLD->push_back(new Tes4SubRecordDoubleLong("NAM0", 0, 0));
	pWRLD->push_back(new Tes4SubRecordDoubleLong("NAM9", 1218969600, 1219493888));

	//  prepare group type 1
	pGrpWRLD0->push_back(pGrpWRLD1);
	pSubHEDR->_numRecords++;
	pGrpWRLD1->_labelL = pWRLD->_id;

	verbose0("  got heights by %d x %d sized bitmap\n  generating tree structure", pBitmapVHGT->_width, pBitmapVHGT->_height);

	//  generate world cell structure
	for (bmpY=0; bmpY < pBitmapVHGT->_height; bmpY += SIZE_CELL_32) {
		posMapY32 = (long) (bmpY / SIZE_CELL_32);
		posMapY64 = (long) (bmpY / SIZE_CELL_64);
		
		for (bmpX=0; bmpX < pBitmapVHGT->_width; bmpX += SIZE_CELL_32) {
			posMapX32 = (long) (bmpX / SIZE_CELL_32);
			posMapX64 = (long) (bmpX / SIZE_CELL_64);

			//  check on existing LAND mappings
			sprintf(coordBuf, "%d;%d", posMapX64, posMapY64);
			if (_mapRecordsLands.count(coordBuf) <= 0) {
				continue;
			}

			//  prepare group type 4
			if ((cntGROUP5 % MAX_GROUP5_PER_GROUP4) == 0) {
				pGrpType4 = new Tes4RecordGroup(stGRUPTYPE4);
				pSubHEDR->_numRecords++;
				pGrpWRLD1->push_back(pGrpType4);

			}  //  if ((cntGROUP5 % MAX_GROUP5_PER_GROUP4) == 0)
			
			//  prepare group type 5
			if ((cntCELL % MAX_CELLS_PER_GROUP5) == 0) {
				pGrpType5 = new Tes4RecordGroup(stGRUPTYPE5);
				pSubHEDR->_numRecords++;
				pGrpType4->push_back(pGrpType5);
				++cntGROUP5;

			}  //  if ((cntCELL % MAX_CELLS_PER_GROUP5) == 0)

			//  prepare CELL
			pCELL = new Tes4RecordGeneric("CELL", _objectId++);
			pSubHEDR->_numRecords++;
			pGrpType5->push_back(pCELL);
			pCELL->push_back(new Tes4SubRecordSingleUShort("DATA", 0x002));
			pCELL->push_back(new Tes4SubRecordXCLCCELL("XCLC", posMapX32, posMapY32));
			++cntCELL;

			//  prepare group type 6
			pGrpType6 = new Tes4RecordGroup(stGRUPTYPE6);
			pSubHEDR->_numRecords++;
			pGrpType5->push_back(pGrpType6);
			pGrpType6->_labelL = pCELL->_id;

			//  prepare group type 9
			pGrpType9 = new Tes4RecordGroup(stGRUPTYPE9);
			pSubHEDR->_numRecords++;
			pGrpType6->push_back(pGrpType9);
			pGrpType9->_labelL = pCELL->_id;

			//  prepare LAND
			pLAND = new Tes4RecordGeneric("LAND", _objectId++);
			pSubHEDR->_numRecords++;
			pGrpType9->push_back(pLAND);
			pLAND->push_back(new Tes4SubRecordFlags("DATA", 0x0000001F));

			//  prepare VGHT
			if (pOptions->_convertTypes & TES_CONVERT_TYPE_HEIGHT_MAP) {
				pSubVHGT = new Tes4SubRecordVHGT(0.0);
				pLAND->push_back(pSubVHGT);
			}

			//  prepare VNML
			if (pOptions->_convertTypes & TES_CONVERT_TYPE_COLOR_MAP) {
				pSubVCLR = new Tes4SubRecordVNML();
				pLAND->push_back(pSubVCLR);
			}

			//  build height map
			int		lastHeightX(0);
			int		lastHeightY(0);

			for (short pixY(0); pixY <= SIZE_CELL_32; ++pixY) {
				for (short pixX(0); pixX <= SIZE_CELL_32; ++pixX) {

					//  write VHGT (map heights)
					if (pSubVHGT != nullptr) {
						TesColor&	color     ((*pBitmapVHGT)(bmpX+pixX, bmpY+pixY));
						int			realHeight((color._r << 16) + (color._g << 8) + color._b);

						if (color._r & 0x80) {
							realHeight |= 0xff000000;
						}

						//  calculate offset for first pixel of cell
						if ((pixX == 0) && (pixY == 0)) {
							pSubVHGT->_offset = (float) realHeight;
							lastHeightX = realHeight;
							lastHeightY = realHeight;
						} else if (pixX == 0) {
							lastHeightX = lastHeightY;
							lastHeightY = realHeight;
						}

						pSubVHGT->_height[pixY][pixX] = (unsigned char) (realHeight - lastHeightX);
						lastHeightX = realHeight;
					}

					//  write VNML (vertex colors)
					if (pSubVCLR != nullptr) {
						Tes4SubRecordVNML::BufferEntry&		pixel(pSubVCLR->_buffer[pixY][pixX]);
						TesColor&							color((*pBitmapVCLR)(bmpX+pixX, bmpY+pixY));

						pixel._xr = color._r;
						pixel._yg = color._g;
						pixel._zb = color._b;
					}
				}  //  for (short pixX(0); pixX <= SIZE_CELL_32; ++pixX)
			}  //  for (short pixY(0); pixY <= SIZE_CELL_32; ++pixY)

			//  Land Textures
			if (pOptions->_convertTypes & TES_CONVERT_TYPE_TEXTURES) {
				unsigned int	offMapX32(posMapX32 * SIZE_CELL_16/2);
				unsigned int	offMapY32(posMapY32 * SIZE_CELL_16/2);

				for (short quadrant(0); quadrant < 4; ++quadrant) {
					map<unsigned int, vector<unsigned short>>	textPlaces;

					for (short pixY(0); pixY <= SIZE_CELL_16; ++pixY) {
						for (short pixX(0); pixX <= SIZE_CELL_16; ++pixX) {
							unsigned int	bitmapX(offMapX32 + (quadrant % 2)*4 + pixX/4);
							unsigned int	bitmapY(offMapY32 + (quadrant / 2)*4 + pixY/4);

							if ((bitmapX < pBitmapVTEX->_width) && (bitmapY < pBitmapVTEX->_height)) {
								TesColor&		color  ((*pBitmapVTEX)(bitmapX, bitmapY));

								textPlaces[(color._b >> 3) | (color._g << 2) | (color._r << 7)].push_back(pixY * 17 + pixX);
							} else {
								textPlaces[0x00000000].push_back(pixY * 17 + pixX);
							}
						}
					}

					unsigned short	idx(0);
					for (auto& texture : textPlaces) {
						//  map texture id...
						unsigned long	textureId(pMapStore->mapTes3Id(texture.first));

						if (idx == 0) {
							pLAND->push_back(new Tes4SubRecordBTXT(quadrant, textureId));
						} else {
							pLAND->push_back(new Tes4SubRecordATXT(quadrant, textureId, idx-1));
							pLAND->push_back(new Tes4SubRecordVTXT(1.0, texture.second));
						}

						++idx;
					}  //  for (auto& texture : textPlaces)
				}  //  for (short quadrant(0); quadrant < 4; ++quadrant)
			}  //  if (pOptions->_convertTypes & TES_CONVERT_TYPE_TEXTURES)
		}  //  for (bmpX=0; bmpX < pBitmapVHGT->_width; bmpX += SIZE_CELL_32)
	}  //  for (bmpY=0; bmpY < pBitmapVHGT->_height; bmpY += SIZE_CELL_32)

	//  calculate tree size recursively
	verbose0("done.\n  calculating node sizes");
	pSubHEDR->_nextObjectId = _objectId;
	tes4Header.calcSizes();

	//  write tree to file
	verbose0("done.\n  writing esp file");
	FILE*	pFile(fopen((fileName).c_str(), "wb"));

	if (pFile != nullptr) {
		tes4Header.writeFile(pFile);
		fflush(pFile);
		fclose(pFile);
		verbose0("done.");
	} else {
		verbose0("can't open out file");
	}

	//tes4Header.dump(0);

	return true;
}
