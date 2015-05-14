#include "common/util/tesoptions.h"
#include <unistd.h>

//-----------------------------------------------------------------------------
TESOptions*	TESOptions::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESOptions::TESOptions()
	:	_verbose      (false),
		_dumpFinalS   (false),
		_dumpFinalT   (false),
		_drawGrid     (false),
		_targetVersion(0)
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
	while ((opt = getopt(argc, argv, "C:d:gL:m:o:t:vV:")) != -1) {
		switch (opt) {
			case 'C':
				_fileNameC = optarg;
				if (_fileNameC.empty() || (_fileNameC[0] == '-')) {
					return false;
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
					return false;
				}
				break;
			case 'g':
				_drawGrid = true;
				break;
			case 'L':
				_fileNameL = optarg;
				if (_fileNameL.empty() || (_fileNameL[0] == '-')) {
					return false;
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
					return false;
				}
				break;
			case 'o':
				_fileNameT = optarg;
				if (_fileNameT.empty() || (_fileNameT[0] == '-')) {
					return false;
				}
				break;
			case 't':
				_targetVersion = atoi(optarg);
				if ((_targetVersion < 3) || (_targetVersion > 4)) {
					return false;
				}
				break;
			case 'V':
				_fileNameH = optarg;
				if (_fileNameH.empty() || (_fileNameH[0] == '-')) {
					return false;
				}
				break;
			case 'v':
				_verbose = true;
				break;
			default:
				return false;
		}
	}

	//  check input file name (at least one needed))
	if (optind >= argc) {
		return false;
	}
	
	//  check parameters
	if ((_targetVersion != 0) && _fileNameT.empty()) {
		printf("Please specify outfile with -o for option -t%d\n", _targetVersion);
		return false;
	}

	return true;
}