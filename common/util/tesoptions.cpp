#include "common/util/tesoptions.h"



//-----------------------------------------------------------------------------
TESOptions*	TESOptions::_pInstance = nullptr;

//-----------------------------------------------------------------------------
TESOptions::TESOptions()
	:	_verbose   (false),
		_dumpFinalS(false),
		_dumpFinalT(false),
		_drawGrid  (false)
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