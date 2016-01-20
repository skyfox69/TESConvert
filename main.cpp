#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>
#include "common/util/tesoptions.h"
#include "common/tesprocessor.h"

using namespace std;

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//  parse options
	if (!TESOptions::getInstance()->parse(argc, argv)) {
		delete TESOptions::getInstance();
		exit(EX_USAGE);
	}
	
	//  initialize worker and process
	TesProcessor::getInstance()->process(argc, argv, optind);

	//  clean up
	delete TesProcessor::getInstance();
	delete TESOptions::getInstance();

	return EX_OK;
}
