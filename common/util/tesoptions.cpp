#include "common/util/tesoptions.h"
#include <unistd.h>

//-----------------------------------------------------------------------------
TESOptions*	TESOptions::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESOptions::TESOptions()
	:	_verbose       (false),
		_dumpFinalS    (false),
		_dumpFinalT    (false),
		_drawGrid      (false),
		_dumpCompressed(0),
		_targetVersion (0)
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
	while ((opt = getopt(argc, argv, "C:d:D:gL:m:o:t:vV:w:")) != -1) {
		switch (opt) {
			case 'C':
				_fileNameC = optarg;
				if (_fileNameC.empty() || (_fileNameC[0] == '-')) {
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
				else {
					return usage();
				}
				break;
			case 'D':
				_dumpCompressed = 1;
				if (*optarg == 'l') {
					_dumpCompressed = 2;
				}
				break;
			case 'g':
				_drawGrid = true;
				break;
			case 'L':
				_fileNameL = optarg;
				if (_fileNameL.empty() || (_fileNameL[0] == '-')) {
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
					return usage();
				}
				break;
			case 'o':
				_fileNameT = optarg;
				if (_fileNameT.empty() || (_fileNameT[0] == '-')) {
					return usage();
				}
				break;
			case 't':
				_targetVersion = atoi(optarg);
				if ((_targetVersion < 3) || (_targetVersion > 4)) {
					return usage();
				}
				break;
			case 'V':
				_fileNameH = optarg;
				if (_fileNameH.empty() || (_fileNameH[0] == '-')) {
					return usage();
				}
				break;
			case 'v':
				_verbose = true;
				break;
			case 'w':
				_worldspace = optarg;
				if (_worldspace.empty() || (_worldspace[0] == '-')) {
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
			"  -C FILE\t\twrite vertex colors to <FILE>.bmp\n"
			"  -D[l]\t\t\tdump compressed parts into files, Dl = last part only (export only)\n"
			"  -ds\t\t\tdump final token structure sort by file sequence\n"
			"  -dt\t\t\tdump final token structure sort by token\n"
			"  -g\t\t\tdraw square cell sized grids on all image exports\n"
			"  -L FILE\t\twrite texture occurance to <FILE>.bmp\n"
			"  -m x,y\t\tdraw mark on cell at x,y\n"
			"  -o FILE\t\tname of outfile for conversion target\n"
			"  -t[3|4]\t\tconvert to target version TES3 or TES4\n"
			"  -V FILE\t\twrite vertex heights to <FILE>.bmp\n"
			"  -v\t\t\tverbose - more output\n"
			"  -w WORLDSPACE\t\tname of worldspace to export/import (TES4 only)\n"
			"\n"
		);

	return false;
}