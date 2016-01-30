#include "common/util/verbosity.h"
#include "common/util/tesoptions.h"
#include <stdarg.h>
#include <stdio.h>

#define	MAX_VEBOSE_LINE_LENGTH		1000

//-----------------------------------------------------------------------------
Verbosity::Verbosity()
{
	_verboseLevel = TESOptions::getInstance()->_verboseLevel;
}

//-----------------------------------------------------------------------------
Verbosity::~Verbosity()
{}

//-----------------------------------------------------------------------------
void Verbosity::verbose0(const char* format, ...)
{
	va_list	ap;
	char	cBuffer[MAX_VEBOSE_LINE_LENGTH] = {0};

	va_start(ap, format);
	vsnprintf(cBuffer, MAX_VEBOSE_LINE_LENGTH, format, ap);

	fprintf(stderr, "%s\n", cBuffer);

	va_end(ap);
}

//-----------------------------------------------------------------------------
void Verbosity::verbose1(const char* format, ...)
{
	if (_verboseLevel > 0) {
		va_list	ap;
		char	cBuffer[MAX_VEBOSE_LINE_LENGTH] = {0};

		va_start(ap, format);
		vsnprintf(cBuffer, MAX_VEBOSE_LINE_LENGTH, format, ap);

		fprintf(stderr, "%s\n", cBuffer);

		va_end(ap);
	}
}

//-----------------------------------------------------------------------------
void Verbosity::verbose2(const char* format, ...)
{
	if (_verboseLevel > 1) {
		va_list	ap;
		char	cBuffer[MAX_VEBOSE_LINE_LENGTH] = {0};

		va_start(ap, format);
		vsnprintf(cBuffer, MAX_VEBOSE_LINE_LENGTH, format, ap);

		fprintf(stderr, "%s\n", cBuffer);

		va_end(ap);
	}
}
