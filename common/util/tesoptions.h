#ifndef TESOPTIONS_H
#define	TESOPTIONS_H

#include <string>
#include "common/types/tesoutformattype.h"

using namespace std;

class TESOptions
{
	private:
		static	TESOptions*					_pInstance;

	protected:
											TESOptions();

	public:
		string								_fileNameC;
		string								_fileNameH;
		string								_fileNameL;
		string								_fileNameT;
		string								_markPos;
		string								_worldspace;
		bool								_verbose;
		bool								_dumpFinalT;
		bool								_dumpFinalS;
		bool								_dumpFinalX;
		bool								_dumpUsedTags;
		bool								_drawGrid;
		TesOutFormatType					_outFormatType;
		unsigned char						_dumpCompressed;
		unsigned char						_targetVersion;

		virtual								~TESOptions();
		static	TESOptions*					getInstance();
		
		virtual bool						parse(int argc, char** argv);
		virtual	bool						usage();
};
#endif  /* TESOPTIONS_H */
