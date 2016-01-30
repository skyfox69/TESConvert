#ifndef VERBOSITY_H
#define	VERBOSITY_H

//-----------------------------------------------------------------------------
class Verbosity
{
	private:
		unsigned char		_verboseLevel;

	protected:
							Verbosity();
		virtual				~Verbosity();

		virtual	void		verbose0(const char* format, ...);
		virtual	void		verbose1(const char* format, ...);
		virtual	void		verbose2(const char* format, ...);
};

#endif	/* VERBOSITY_H */

