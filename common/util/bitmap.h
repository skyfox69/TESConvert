#ifndef BITMAP_H
#define	BITMAP_H

#include <string>

using namespace std;

//-----------------------------------------------------------------------------
struct TesColor {
	unsigned char				_r;
	unsigned char				_g;
	unsigned char				_b;
	unsigned short				_i;

								TesColor(unsigned char const r=0, unsigned char const g=0, unsigned char const b=0);
								~TesColor();
	unsigned char&				operator[](unsigned int const idx);
	TesColor&					assign(unsigned char const r, unsigned char const g, unsigned char const b);
};

int operator==(const TesColor& a, const TesColor& b);
int operator!=(const TesColor& a, const TesColor& b);

//-----------------------------------------------------------------------------
class Bitmap {
	public:
		TesColor*				_pRGB;
		unsigned int			_width;
		unsigned int			_height;

	private:
		virtual	unsigned char*	writeBmpHeader(unsigned char* pData, size_t fileSize, size_t bmSize);
		virtual	unsigned char*	writeBmpHeaderGrey(unsigned char* pData, size_t fileSize, size_t bmSize);

		virtual	void			rescaleForGreyScale(float const factor);

	public:
								Bitmap(unsigned int const width=0, unsigned int const height=0);
		virtual					~Bitmap();

		virtual	void			clear(unsigned short const r=0x0000, unsigned short const g=0x0000, unsigned short const b=0x0000);

		virtual void			write(string const fileName);
		virtual void			writeBmp24(string const fileName);
		virtual void			writeBmp8g(string const fileName);
		virtual void			writePng24(string const fileName);
		virtual void			writePng16(string const fileName);
		
		TesColor&				operator()(unsigned int const x, unsigned int const y);
		const	TesColor&		operator()(unsigned int const x, unsigned int const y) const;
		unsigned char&			operator()(unsigned int const x, unsigned int const y, unsigned int const idx);
		const	unsigned char&	operator()(unsigned int const x, unsigned int const y, unsigned int const idx) const;
};

#endif	/* BITMAP_H */