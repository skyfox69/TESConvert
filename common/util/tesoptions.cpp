#include "common/util/tesoptions.h"
#include <unistd.h>
#include <cstring>

//-----------------------------------------------------------------------------
TESOptions*	TESOptions::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESOptions::TESOptions()
	:	_fileNameM     ("./textures.map"),
		_convertTypes  (TES_CONVERT_TYPE_ALL),
		_dumpFinalS    (false),
		_dumpFinalT    (false),
		_dumpFinalX    (false),
		_drawGrid      (false),
		_dumpUsedTags  (false),
		_doCompress    (false),
		_outFormatType (TesOutFormatType::BMP_24),
		_dumpCompressed(0),
		_targetVersion (0),
		_verboseLevel  (0)
{}

//-----------------------------------------------------------------------------
TESOptions::~TESOptions()
{}

//-----------------------------------------------------------------------------
TESOptions* TESOptions::getInstance()
{
	if (_pInstance == nullptr) {
		_pInstance = new TESOptions();
	}
	
	return _pInstance;
}

//-----------------------------------------------------------------------------
bool TESOptions::parse(int argc, char** argv)
{
	int		opt           (0);
	bool	wasConvertType(false);

	//  decode options
	while ((opt = getopt(argc, argv, "a:c:C:d:D:f:gH:m:M:n:o:pt:T:v:w:")) != -1) {
		switch (opt) {
			case 'a':
				_expToken = optarg;
				break;
			case 'c':
				if (*optarg == 'a') {
					_convertTypes = TES_CONVERT_TYPE_ALL;
				} else {
					if (!wasConvertType) {
						_convertTypes  = 0x0000;
						wasConvertType = true;
					}
					if (*optarg == 'c') {
						_convertTypes |= TES_CONVERT_TYPE_COLOR_MAP;
					} else if (*optarg == 'h') {
						_convertTypes |= TES_CONVERT_TYPE_HEIGHT_MAP;
					} else if (*optarg == 't') {
						_convertTypes |= TES_CONVERT_TYPE_TEXTURES;
					}
				}
				break;
			case 'C':
				_fileNameC = optarg;
				if (_fileNameC.empty() || (_fileNameC[0] == '-')) {
					printf("\x1B[31mPlease specify a filename!\033[0m\n");
					return usage();
				}
				break;
			case 'd':
				if (*optarg == 't') {
					_dumpFinalT = true;
				}
				else if (*optarg == 's') {
					_dumpFinalS = true;
				}
				else if (*optarg == 'x') {
					_dumpFinalX = true;
				}
				else if (*optarg == 'u') {
					_dumpUsedTags = true;
				}
				else {
					printf("\x1B[31mUnknown dump format!\033[0m\n");
					return usage();
				}
				break;
			case 'D':
				_dumpCompressed = 1;
				if (*optarg == 'l') {
					_dumpCompressed = 2;
				}
				break;
			case 'f':
				if (strcasecmp(optarg, "BMP24") == 0) {
					_outFormatType = TesOutFormatType::BMP_24;
				} else  if (strcasecmp(optarg, "BMP8") == 0) {
					_outFormatType = TesOutFormatType::BMP_8_GREY;
				} else if (strcasecmp(optarg, "PNG24") == 0) {
					_outFormatType = TesOutFormatType::PNG_24;
				} else if (strcasecmp(optarg, "PNG16") == 0) {
					_outFormatType = TesOutFormatType::PNG_16_GREY;
				} else {
					printf("\x1B[31mUnknown output file format!\033[0m\n");
					return usage();
				}
				break;
			case 'g':
				_drawGrid = true;
				break;
			case 'H':
				_fileNameH = optarg;
				if (_fileNameH.empty() || (_fileNameH[0] == '-')) {
					printf("\x1B[31mPlease specify a filename!\033[0m\n");
					return usage();
				}
				break;
			case 'm':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a master name!\033[0m\n");
					return usage();
				}
				_masterNames.push_back(optarg);
				break;
			case 'M':
				_fileNameM = optarg;
				if (_fileNameM.empty() || (_fileNameM[0] == '-')) {
					printf("\x1B[31mPlease specify a texture mapping filename!\033[0m\n");
					return usage();
				}
				break;
			case 'n':
				_markPos = optarg;
				if (!_markPos.empty()) {
					for (auto aChar : _markPos) {
						fprintf(stderr, "%c", aChar);
						if (!isdigit(aChar) && (aChar != '-') && (aChar != ',')) {
							_markPos = "";
							break;
						}
					}
				}
				if (_markPos.empty()) {
					printf("\x1B[31mPlease specify a valid position!\033[0m\n");
					return usage();
				}
				break;
			case 'o':
				_fileNameT = optarg;
				if (_fileNameT.empty() || (_fileNameT[0] == '-')) {
					printf("\x1B[31mPlease specify a filename!\033[0m\n");
					return usage();
				}
				if (_fileNameT.find(".esp") == string::npos) {
					_fileNameT += ".esp";
				}
				break;
			case 'p':
				_doCompress = true;
				break;
			case 't':
				_targetVersion = atoi(optarg);
				if ((_targetVersion < 3) || (_targetVersion > 4)) {
					printf("\x1B[31mPlease specify a valid target version!\033[0m\n");
					return usage();
				}
				break;
			case 'T':
				_fileNameL = optarg;
				if (_fileNameL.empty() || (_fileNameL[0] == '-')) {
					printf("\x1B[31mPlease specify a filename!\033[0m\n");
					return usage();
				}
				break;
			case 'v':
				_verboseLevel = atoi(optarg);
				break;
			case 'w':
				_worldspace = optarg;
				if (_worldspace.empty() || (_worldspace[0] == '-')) {
					printf("\x1B[31mPlease specify a valid workspace or list option!\033[0m\n");
					return usage();
				}
				break;
			default:
				return usage();
		}
	}

	//  check input file name (at least one needed))
	if (optind >= argc) {
		return usage();
	}
	
	//  check parameters
	if ((_targetVersion != 0) && _fileNameT.empty()) {
		printf("Please specify outfile with -o for option -t%d\n", _targetVersion);
		return usage();
	}

	return true;
}

//-----------------------------------------------------------------------------
bool TESOptions::usage()
{
	printf("\nUsage: tesconvert OPTION TES-filename ...\n"
			"Parse TES file (ESM/ESP) and analyse structure.\n\n"
			"  -a TOKEN\t\tdump TOKEN only\n"
			"  -c TYPE\t\ttype of data to be converted (multiple occurances possible):\n"
			"\t\t\t  a=all (default), c=color-map, h=height-map, t=textures\n"
			"  -C FILE\t\twrite vertex colors to <FILE>.<ext-by-format>\n"
			"  -D[l]\t\t\tdump compressed parts into files, Dl = last part only (export only)\n"
			"  -ds\t\t\tdump final token structure sort by file sequence\n"
			"  -dt\t\t\tdump final token structure sort by token\n"
			"  -du\t\t\tdump all used tokens\n"
			"  -dx\t\t\tdump final token structure sort by file appearance as XML\n"
			"  -f FORMAT\t\tformat of image files (BMP24, BMP8, PNG24, PNG16), default: BMP24\n"
			"  -g\t\t\tdraw square cell sized grids on all image exports\n"
			"  -H FILE\t\twrite vertex heights to <FILE>.<ext-by-format>\n"
			"  -m NAME\t\tspecify master name, multiple occurances possible\n"
			"  -M FILE\t\tread texture mapping from FILE (default: textures.map)\n"
			"  -n x,y\t\tdraw mark on cell at x,y\n"
			"  -o FILE\t\tname of outfile for conversion target\n"
			"  -p\t\t\tcompress TES4 data where possible (e.g. LAND)\n"
			"  -t[3|4]\t\tconvert to target version TES3 or TES4\n"
			"  -T FILE\t\twrite texture occurance to <FILE>.<ext-by-format>\n"
			"  -v LEVEL\t\tverbose - more output\n"
			"  -w [l|WORLDSPACE]\tname of worldspace to export/import, -wl to list all worldspaces (TES4 only)\n"
			"\n"
		);

	return false;
}
