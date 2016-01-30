#include "common/util/compressor.h"
#include <zlib.h>

//-----------------------------------------------------------------------------
int Compressor::deflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst)
{
	z_stream	strm = {0};
	int			retCode(-1);

	strm.avail_in  = lenSrc;
	strm.avail_out = lenDst;
	strm.next_in   = (Bytef*) pBufSrc;
	strm.next_out  = (Bytef*) pBufDst;
	strm.zalloc    = Z_NULL;
	strm.zfree     = Z_NULL;
	strm.opaque    = Z_NULL;

	retCode = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
	if (retCode == Z_OK) {
		retCode = deflate(&strm, Z_FINISH);
		if (retCode == Z_STREAM_END) {
			retCode = strm.total_out;
		}
	}

	deflateEnd(&strm);

	return retCode;
}

//-----------------------------------------------------------------------------
int Compressor::inflateBuffer(const void* pBufSrc, const int lenSrc, void* pBufDst, const int lenDst)
{
	z_stream	strm = {0};
	int			retCode(-1);

	strm.total_in  = lenSrc;
	strm.avail_in  = lenSrc;
	strm.total_out = lenDst;
	strm.avail_out = lenDst;
	strm.next_in   = (Bytef*) pBufSrc;
	strm.next_out  = (Bytef*) pBufDst;
	strm.zalloc    = Z_NULL;
	strm.zfree     = Z_NULL;
	strm.opaque    = Z_NULL;

	retCode = inflateInit2(&strm, (15 + 32));
	if (retCode == Z_OK) {
		retCode = inflate(&strm, Z_FINISH);
		if (retCode == Z_STREAM_END) {
			retCode = strm.total_out;
		}
	}

	inflateEnd(&strm);

	return retCode;
}