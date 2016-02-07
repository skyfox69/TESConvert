#ifndef COMPRESSOR_H
#define	COMPRESSOR_H

//-----------------------------------------------------------------------------
class Compressor {
	public:
		static	int		deflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst);
		static	int		inflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst);
};

#endif	/* COMPRESSOR_H */