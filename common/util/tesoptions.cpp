#include "common/util/tesoptions.h"
#include <unistd.h>
#include <cstring>

//-----------------------------------------------------------------------------
TESOptions*	TESOptions::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESOptions::TESOptions()
	:	_dumpFinalS    (false),
		_dumpFinalT    (false),
		_dumpFinalX    (false),
		_drawGrid      (false),
		_dumpUsedTags  (false),
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
	int		opt(0);

	//  decode options
	while ((opt = getopt(argc, argv, "C:d:D:f:gL:m:o:t:v:V:w:")) != -1) {
		switch (opt) {
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
			case 'L':
				_fileNameL = optarg;
				if (_fileNameL.empty() || (_fileNameL[0] == '-')) {
					printf("\x1B[31mPlease specify a filename!\033[0m\n");
					return usage();
				}
				break;
			case 'm':
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
				break;
			case 't':
				_targetVersion = atoi(optarg);
				if ((_targetVersion < 3) || (_targetVersion > 4)) {
					printf("\x1B[31mPlease specify a valid target version!\033[0m\n");
					return usage();
				}
				break;
			case 'V':
				_fileNameH = optarg;
				if (_fileNameH.empty() || (_fileNameH[0] == '-')) {
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
			"  -C FILE\t\twrite vertex colors to <FILE>.<ext-by-format>\n"
			"  -D[l]\t\t\tdump compressed parts into files, Dl = last part only (export only)\n"
			"  -ds\t\t\tdump final token structure sort by file sequence\n"
			"  -dt\t\t\tdump final token structure sort by token\n"
			"  -du\t\t\tdump all used tokens\n"
			"  -dx\t\t\tdump final token structure sort by file appearance as XML\n"
			"  -f FORMAT\t\tformat of image files (BMP24, BMP8, PNG24, PNG16), default: BMP24\n"
			"  -g\t\t\tdraw square cell sized grids on all image exports\n"
			"  -L FILE\t\twrite texture occurance to <FILE>.<ext-by-format>\n"
			"  -m x,y\t\tdraw mark on cell at x,y\n"
			"  -o FILE\t\tname of outfile for conversion target\n"
			"  -t[3|4]\t\tconvert to target version TES3 or TES4\n"
			"  -V FILE\t\twrite vertex heights to <FILE>.<ext-by-format>\n"
			"  -v LEVEL\t\tverbose - more output\n"
			"  -w [l|WORLDSPACE]\tname of worldspace to export/import, -wl to list all worldspaces (TES4 only)\n"
			"\n"
		);

	return false;
}
