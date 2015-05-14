#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>
#include "common/util/tesoptions.h"
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
			"  -o FILE\tname of outfile for conversion target\n"
			"  -t[3|4]\tconvert to target version TES3 or TES4\n"
			"  -V FILE\twrite vertex heights to <FILE>.bmp\n"
			"  -v\t\tverbose - more output\n"
			"\n"
		);
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//  parse options
	if (!TESOptions::getInstance()->parse(argc, argv)) {
		usage();
		exit(EX_USAGE);
	}
	
	//  initialize worker and process
	TesProcessor::getInstance()->process(argc, argv, optind);

	//  clean up
	delete TESOptions::getInstance();

	return EX_OK;
}
