#ifndef TESOPTIONS_H
#define	TESOPTIONS_H

#include <string>
#include <vector>
#include "common/types/tesoutformattype.h"

using namespace std;

//-----------------------------------------------------------------------------
//  convert types
#define	TES_CONVERT_TYPE_COLOR_MAP		0x0001
#define	TES_CONVERT_TYPE_HEIGHT_MAP		0x0002
#define	TES_CONVERT_TYPE_TEXTURES		0x0004
#define	TES_CONVERT_TYPE_ALL			TES_CONVERT_TYPE_COLOR_MAP | TES_CONVERT_TYPE_HEIGHT_MAP | TES_CONVERT_TYPE_TEXTURES

//-----------------------------------------------------------------------------
class TESOptions
{
	private:
		static	TESOptions*					_pInstance;

	protected:
											TESOptions();

	public:
		vector<string>						_masterNames;
		string								_fileNameC;
		string								_fileNameH;
		string								_fileNameL;
		string								_fileNameT;
		string								_fileNameM;
		string								_markPos;
		string								_worldspace;
		string								_expToken;
		unsigned short						_convertTypes;
		bool								_dumpFinalT;
		bool								_dumpFinalS;
		bool								_dumpFinalX;
		bool								_dumpUsedTags;
		bool								_drawGrid;
		bool								_doCompress;
		TesOutFormatType					_outFormatType;
		unsigned char						_dumpCompressed;
		unsigned char						_targetVersion;
		unsigned char						_verboseLevel;

		virtual								~TESOptions();
		static	TESOptions*					getInstance();
		
		virtual bool						parse(int argc, char** argv);
		virtual	bool						usage();
};
#endif  /* TESOPTIONS_H */
