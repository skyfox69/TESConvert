#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sysexits.h>
#include "common/util/tesoptions.h"
#include "common/tesprocessor.h"
#include "tes3/record/tes3recordgeneric.h"
#include "common/tesprocessor.h"

using namespace std;

//-----------------------------------------------------------------------------
void usage()
{
	printf("\nUsage: tesconvert OPTION TES-filename ...\n"
			"Parse TES file (ESM/ESP) and analyse structure.\n\n"
			"  -C FILE\twrite vertex colors to <FILE>.bmp\n"
			"  -ds\t\tdump final token structure sort by file sequence\n"
			"  -dt\t\tdump final token structure sort by token\n"
			"  -g\t\tdraw square cell sized grids on all image exports\n"
			"  -L FILE\twrite texture occurance to <FILE>.bmp\n"
			"  -m x,y\tdraw mark on cell at x,y\n"
			"  -V FILE\twrite vertex heights to <FILE>.bmp\n"
			"  -v\t\tverbose - more output\n"
			"\n"
		);
	exit(EX_USAGE);
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	TESOptions*		pOptions(TESOptions::getInstance());
	int				opt(0);

	//  decode options
	while ((opt = getopt(argc, argv, "C:d:gL:m:vV:")) != -1) {
		switch (opt) {
			case 'C':
				pOptions->_fileNameC = optarg;
				if (pOptions->_fileNameC.empty() || (pOptions->_fileNameC[0] == '-')) {
					usage();
					exit(EX_USAGE);
				}
				break;
			case 'd':
				if (*optarg == 't') {
					pOptions->_dumpFinalT = true;
				}
				else if (*optarg == 's') {
					pOptions->_dumpFinalS = true;
				}
				else {
					usage();
					exit(EX_USAGE);
				}
				break;
			case 'g':
				pOptions->_drawGrid = true;
				break;
			case 'L':
				pOptions->_fileNameL = optarg;
				if (pOptions->_fileNameL.empty() || (pOptions->_fileNameL[0] == '-')) {
					usage();
					exit(EX_USAGE);
				}
				break;
			case 'm':
				pOptions->_markPos = optarg;
				if (!pOptions->_markPos.empty()) {
					for (auto aChar : pOptions->_markPos) {
						fprintf(stderr, "%c", aChar);
						if (!isdigit(aChar) && (aChar != '-') && (aChar != ',')) {
							pOptions->_markPos = "";
							break;
						}
					}
				}
				if (pOptions->_markPos.empty()) {
					usage();
					exit(EX_USAGE);
				}
				break;
			case 'V':
				pOptions->_fileNameH = optarg;
				if (pOptions->_fileNameH.empty() || (pOptions->_fileNameH[0] == '-')) {
					usage();
					exit(EX_USAGE);
				}
				break;
			case 'v':
				pOptions->_verbose = true;
				break;
			default:
				usage();
		}
	}

	//  check input file name (at least one needed))
	if (optind >= argc) {
		usage();
	}
	
	//  initialize worker
	TesProcessor	tesProcessor;
	bool			isParsed(true);
	
	for (int i(optind); (i < argc) && isParsed; ++i) {
		isParsed &= tesProcessor.parse(argv[i]);
	}
	
	if (isParsed) {
		//  dump token structure
		if (pOptions->_dumpFinalT) {
			tesProcessor.dumpTokensByName();
		}
		if (pOptions->_dumpFinalS) {
			tesProcessor.dumpTokensBySequence();
		}
		
		
		
		//  dump vertex color map
		if (!pOptions->_fileNameC.empty()) {
			tesProcessor.dumpVclrMap(pOptions->_fileNameC);
		}
		//  dump height map
		if (!pOptions->_fileNameH.empty()) {
			tesProcessor.dumpVhgtMap(pOptions->_fileNameH);
		}
		//  dump texture map
		if (!pOptions->_fileNameL.empty()) {
			tesProcessor.dumpVtexMap(pOptions->_fileNameL);
		}
		
	}

	
#if 0
	//  initialize RecordFactory
	Tes3RecordFactory::getInstance();

	Tes3Parser		tes3Parser((options & 0x10000000) != 0);

	for (int i(optind); (i < argc) && isParsed; ++i) {
		isParsed = tes3Parser.parse(argv[i]);
	}

	if (isParsed) {
		if ((options & 0x00000001) != 0) {		//  d3
			tes3Parser.dumpTes3();
		}
		if ((options & 0x00000010) != 0) {		//  c
			tes3Parser.dumpVclrMap(fileNameC);
		}
		if ((options & 0x00000020) != 0) {		//  v
			tes3Parser.dumpVhgtMap(fileNameV);
		}
	}

	//  clean up
	delete Tes3RecordFactory::getInstance();
#endif
	
	//  clean up
	delete pOptions;

	return EX_OK;
}
