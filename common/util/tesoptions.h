#ifndef TESOPTIONS_H
#define	TESOPTIONS_H

#include <string>

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
		string								_markPos;
		bool								_verbose;
		bool								_dumpFinalT;
		bool								_dumpFinalS;
		bool								_drawGrid;

		virtual								~TESOptions();
		static	TESOptions*					getInstance();
};
#endif  /* TESOPTIONS_H */
