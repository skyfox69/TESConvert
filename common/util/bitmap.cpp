#include "common/util/bitmap.h"
#include "common/util/tesoptions.h"
#include <cstring>
#include <climits>
#include <map>

extern "C"{
#include <png.h>
}

//-----------------------------------------------------------------------------
TesColor::TesColor(const unsigned char r, const unsigned char g, const unsigned char b)
	:	_r(r),
		_g(g),
		_b(b),
		_i(0)
{}

//-----------------------------------------------------------------------------
TesColor::~TesColor()
{}

//-----------------------------------------------------------------------------
unsigned char& TesColor::operator [](const unsigned int idx)
{
	switch (idx) {
		case 0:		return _r;
		case 1:		return _g;
		default:	return _b;
	}
}

//-----------------------------------------------------------------------------
TesColor& TesColor::assign(unsigned char const r, unsigned char const g, unsigned char const b)
{
	_r = r;
	_g = g;
	_b = b;
	_i = 0;

	return *this;
}

//-----------------------------------------------------------------------------
int operator==(const TesColor& a, const TesColor& b)
{
	return !operator!=(a, b);
}

//-----------------------------------------------------------------------------
int operator!=(const TesColor& a, const TesColor& b)
{
	if (a._r != b._r)		return true;
	if (a._g != b._g)		return true;
	if (a._b != b._b)		return true;
	return false;
}

//-----------------------------------------------------------------------------
Bitmap::Bitmap(const unsigned int width, const unsigned int height)
	:	_pRGB  (nullptr),
		_width (width),
		_height(height)
{
	if ((_width > 0) && (_height > 0)) {
		_pRGB = new TesColor[_width * _height];
	}
}

//-----------------------------------------------------------------------------
Bitmap::~Bitmap()
{
	if (_pRGB != nullptr) {
		delete[] _pRGB;
		_pRGB = nullptr;
	}
}

//-----------------------------------------------------------------------------
void Bitmap::clear(unsigned short const r, unsigned short const g, unsigned short const b)
{
	if (_pRGB != nullptr) {
		size_t	size(_width*_height);

		for (size_t pos(0); pos < size; ++pos) {
			_pRGB[pos]._r = r;
			_pRGB[pos]._g = g;
			_pRGB[pos]._b = b;
			_pRGB[pos]._i = 0;
		}
	}
}

//-----------------------------------------------------------------------------
void Bitmap::rescaleForGreyScale(float const factor)
{
	float	scale    (1.0);
	int		heightAct(0);
	int		heightMin(INT_MAX);
	int		heightMax(INT_MIN);
	int		x        (0);
	int		y        (0);

	for (y=0; y < _height; ++y) {
		for (x=0; x < _width; ++x) {
			TesColor&		color((*this)(x, y));

			heightAct = (int) (color._r << 16) + (color._g << 8) + color._b;
			if (color._r & 0x80) {
				heightAct |= 0xff000000;
			}

			if (heightAct < heightMin)		heightMin = heightAct;
			if (heightAct > heightMax)		heightMax = heightAct;

		}  //  for (x=0; x < _width; ++x)
	}  //  for (y=0; y < _height; ++y)

	scale = ((float) (heightMax - heightMin)) / factor;

	for (y=0; y < _height; ++y) {
		for (x=0; x < _width; ++x) {
			TesColor&		color((*this)(x, y));

			heightAct = (int) (color._r << 16) + (color._g << 8) + color._b;
			if (color._r & 0x80) {
				heightAct |= 0xff000000;
			}
			color._i = (short) (((float) (heightAct - heightMin)) / scale);

		}  //  for (x=0; x < _width; ++x)
	}  //  for (y=0; y < _height; ++y)
}

//-----------------------------------------------------------------------------
unsigned char* Bitmap::writeBmpHeader(unsigned char* pData, size_t fileSize, size_t bmSize)
{
	unsigned char*	pStart(pData);
	unsigned char	bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char	bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0, 0,0,0,0,
										 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};

	bmpfileheader[ 2] = (unsigned char)(fileSize    );
	bmpfileheader[ 3] = (unsigned char)(fileSize>> 8);
	bmpfileheader[ 4] = (unsigned char)(fileSize>>16);
	bmpfileheader[ 5] = (unsigned char)(fileSize>>24);
	memcpy(pStart, bmpfileheader, 14);
	pStart += 14;

	bmpinfoheader[ 4] = (unsigned char)( _width    );
	bmpinfoheader[ 5] = (unsigned char)( _width>> 8);
	bmpinfoheader[ 6] = (unsigned char)( _width>>16);
	bmpinfoheader[ 7] = (unsigned char)( _width>>24);
	bmpinfoheader[ 8] = (unsigned char)(_height    );
	bmpinfoheader[ 9] = (unsigned char)(_height>> 8);
	bmpinfoheader[10] = (unsigned char)(_height>>16);
	bmpinfoheader[11] = (unsigned char)(_height>>24);
	bmpinfoheader[20] = (unsigned char)(bmSize     );
	bmpinfoheader[21] = (unsigned char)(bmSize >> 8);
	bmpinfoheader[22] = (unsigned char)(bmSize >>16);
	bmpinfoheader[23] = (unsigned char)(bmSize >>24);
	memcpy(pStart, bmpinfoheader, 40);
	pStart += 40;

	return pStart;
}

//-----------------------------------------------------------------------------
unsigned char* Bitmap::writeBmpHeaderGrey(unsigned char* pData, size_t fileSize, size_t bmSize)
{
	unsigned char*	pStart(pData);
	unsigned char	bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,4,0,0};
	unsigned char	bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 8,0, 0,0,0,0,
										 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};

	bmpfileheader[ 2] = (unsigned char)(fileSize    );
	bmpfileheader[ 3] = (unsigned char)(fileSize>> 8);
	bmpfileheader[ 4] = (unsigned char)(fileSize>>16);
	bmpfileheader[ 5] = (unsigned char)(fileSize>>24);
	memcpy(pStart, bmpfileheader, 14);
	pStart += 14;

	bmpinfoheader[ 4] = (unsigned char)( _width    );
	bmpinfoheader[ 5] = (unsigned char)( _width>> 8);
	bmpinfoheader[ 6] = (unsigned char)( _width>>16);
	bmpinfoheader[ 7] = (unsigned char)( _width>>24);
	bmpinfoheader[ 8] = (unsigned char)(_height    );
	bmpinfoheader[ 9] = (unsigned char)(_height>> 8);
	bmpinfoheader[10] = (unsigned char)(_height>>16);
	bmpinfoheader[11] = (unsigned char)(_height>>24);
	bmpinfoheader[20] = (unsigned char)(bmSize     );
	bmpinfoheader[21] = (unsigned char)(bmSize >> 8);
	bmpinfoheader[22] = (unsigned char)(bmSize >>16);
	bmpinfoheader[23] = (unsigned char)(bmSize >>24);
	memcpy(pStart, bmpinfoheader, 40);
	pStart += 40;

	//  grey color map
	for (unsigned short i(0); i < 256; ++i) {
		*pStart++ = i;
		*pStart++ = i;
		*pStart++ = i;
		*pStart++ = 0;
	}

	return pStart;
}

//-----------------------------------------------------------------------------
void Bitmap::write(const string fileName)
{
	switch (TESOptions::getInstance()->_outFormatType) {
		case TesOutFormatType::BMP_24:
			return writeBmp24(fileName);
		case TesOutFormatType::BMP_8_GREY:
			return writeBmp8g(fileName);
		case TesOutFormatType::PNG_24:
			return writePng24(fileName);
		case TesOutFormatType::PNG_16_GREY:
			return writePng16(fileName);
	}
}

//-----------------------------------------------------------------------------
void Bitmap::writeBmp24(const string fileName)
{
	int				x       (0);
	int				y       (0);
	int				j       (0);
	int				bpp     (24);
	int				diffRow ((4 - (_width * bpp/8)%4)%4);
	size_t			bmSize  ((_width * bpp/8 + diffRow) * _height);
	size_t			fileSize(54 + bmSize);
	unsigned char*	pData   (new unsigned char[fileSize]);
	unsigned char*	pStart  (pData);

	//  clear buffer
	memset(pData, 0, fileSize);

	//  write header
	pStart = writeBmpHeader(pStart, fileSize, bmSize);

	//  write bitmap
	for (y=0; y < _height; ++y) {
		for (x=0; x < _width; ++x) {
			TesColor&		color((*this)(x, y));

			*pStart++ = (unsigned char) color._b;
			*pStart++ = (unsigned char) color._g;
			*pStart++ = (unsigned char) color._r;
		}
		for (j=0; j < diffRow; ++j) {
			*pStart++ = 0;
		}
	}

	//  write buffer to file
	FILE*	pFile(fopen((fileName + ".bmp").c_str(), "wb"));

	if (pFile != nullptr) {
		fwrite(pData, fileSize, 1, pFile);
		fflush(pFile);
		fclose(pFile);
	}

	if (pData != nullptr)	delete[] pData;
}

//-----------------------------------------------------------------------------
void Bitmap::writeBmp8g(const string fileName)
{
	int				x       (0);
	int				y       (0);
	int				j       (0);
	int				bpp     (24);
	int				diffRow ((4 - (_width * bpp/8)%4)%4);
	size_t			bmSize  ((_width * bpp/8 + diffRow) * _height);
	size_t			fileSize(54 + bmSize);
	unsigned char*	pData   (new unsigned char[fileSize]);
	unsigned char*	pStart  (pData);

	//  clear buffer
	memset(pData, 0, fileSize);

	//  write header
	pStart = writeBmpHeaderGrey(pStart, fileSize, bmSize);

	//  rescale for grey scale image
	rescaleForGreyScale(255.01);

	//  write bitmap
	for (y=0; y < _height; ++y) {
		for (x=0; x < _width; ++x) {
			TesColor&		color((*this)(x, y));

			*pStart++ = (unsigned char) color._i;
		}
		for (j=0; j < diffRow; ++j) {
			*pStart++ = 0;
		}
	}
	
	//  write buffer to file
	FILE*	pFile(fopen((fileName + ".bmp").c_str(), "wb"));

	if (pFile != nullptr) {
		fwrite(pData, fileSize, 1, pFile);
		fflush(pFile);
		fclose(pFile);
	}

	if (pData != nullptr)	delete[] pData;
}

//-----------------------------------------------------------------------------
void Bitmap::writePng24(const string fileName)
{
	FILE*	pFile(fopen((fileName + ".png").c_str(), "wb"));

	if (pFile != nullptr) {
		png_struct*		pPng(png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL));

		if (pPng != nullptr) {
			png_info*	pInfo(png_create_info_struct(pPng));

			if (pInfo != nullptr) {
				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during init_io\n");
					abort();
				}

				png_init_io(pPng, pFile);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during writing header\n");
					abort();
				}

				png_set_IHDR(pPng, pInfo, _width, _height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
				png_write_info(pPng, pInfo);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during writing bitmap\n");
					abort();
				}

				int				rowBytes  ((int) png_get_rowbytes(pPng, pInfo));
				int				sizeHeight((int) sizeof(png_byte*) * _height);
				int				sizeRowHgt(rowBytes * _height);
				int				x         (0);
				int				y         (0);
				unsigned int    pixelsTot (_height*_width - 1);
				unsigned char*	pData     (new unsigned char[sizeHeight + sizeRowHgt]);
				unsigned char*	pOffset   (pData + sizeHeight);
				unsigned char*	pStart    (pOffset);
				unsigned char**	ppHeight  ((unsigned char**) pData);

				for (int i(0); i < _height; ++i) {
					ppHeight[i] = pOffset + rowBytes * i;
				}

				//  write bitmap
				for (y=(_height-1); y >= 0; --y) {
					for (x=0; x < _width; ++x) {
						TesColor&		color((*this)(x, y));

						*pStart++ = (unsigned char) color._r;
						*pStart++ = (unsigned char) color._g;
						*pStart++ = (unsigned char) color._b;
					}
				}

				png_write_image(pPng, (png_byte**) pData);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during end of write\n");
					abort();
				}

				png_write_end(pPng, NULL);

				//  clean up
				delete[] pData;
				png_destroy_write_struct(&pPng, &pInfo);

			}  //  if (pInfo != nullptr)
		}  //  if (pPng != nullptr)

		fflush(pFile);
		fclose(pFile);
	}  //  if (pFile != nullptr)
}

//-----------------------------------------------------------------------------
void Bitmap::writePng16(const string fileName)
{
	FILE*	pFile(fopen((fileName + ".png").c_str(), "wb"));

	if (pFile != nullptr) {
		png_struct*		pPng(png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL));

		if (pPng != nullptr) {
			png_info*	pInfo(png_create_info_struct(pPng));

			if (pInfo != nullptr) {
				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during init_io\n");
					abort();
				}

				png_init_io(pPng, pFile);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during writing header\n");
					abort();
				}

				png_set_IHDR(pPng, pInfo, _width, _height, 16, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
				png_write_info(pPng, pInfo);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during writing bitmap\n");
					abort();
				}

				int				rowBytes  ((int) png_get_rowbytes(pPng, pInfo));
				int				sizeHeight((int) sizeof(png_byte*) * _height);
				int				sizeRowHgt(rowBytes * _height);
				int				x         (0);
				int				y         (0);
				unsigned int    pixelsTot (_height*_width - 1);
				unsigned char*	pData     (new unsigned char[sizeHeight + sizeRowHgt]);
				unsigned char*	pOffset   (pData + sizeHeight);
				unsigned char*	pStart    (pOffset);
				unsigned char**	ppHeight  ((unsigned char**) pData);

				for (int i(0); i < _height; ++i) {
					ppHeight[i] = pOffset + rowBytes * i;
				}

				//  rescale for grey scale image
				rescaleForGreyScale(65535.01);

				//  write bitmap
				for (y=(_height-1); y >= 0; --y) {
					for (x=0; x < _width; ++x) {
						TesColor&		color((*this)(x, y));

						*pStart++ = (unsigned char) (color._i >> 8);
						*pStart++ = (unsigned char) (color._i & 0xff);
					}
				}

				png_write_image(pPng, (png_byte**) pData);

				if (setjmp(png_jmpbuf(pPng))) {
					fprintf(stderr, "PNG: error during end of write\n");
					abort();
				}

				png_write_end(pPng, NULL);

				//  clean up
				delete[] pData;
				png_destroy_write_struct(&pPng, &pInfo);

			}  //  if (pInfo != nullptr)
		}  //  if (pPng != nullptr)

		fflush(pFile);
		fclose(pFile);
	}  //  if (pFile != nullptr)
}

//-----------------------------------------------------------------------------
TesColor& Bitmap::operator ()(const unsigned int x, const unsigned int y)
{
	return _pRGB[y*_width + x];
}

//-----------------------------------------------------------------------------
const TesColor& Bitmap::operator ()(const unsigned int x, const unsigned int y) const
{
	return _pRGB[y*_width + x];
}

//-----------------------------------------------------------------------------
unsigned char& Bitmap::operator ()(const unsigned int x, const unsigned int y, unsigned int const idx)
{
	return _pRGB[y*_width + x][idx];
}

//-----------------------------------------------------------------------------
const unsigned char& Bitmap::operator ()(const unsigned int x, const unsigned int y, unsigned int const idx) const
{
	return _pRGB[y*_width + x][idx];
}
