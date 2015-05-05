#include "common/util/endian.h"

//-----------------------------------------------------------------------------
void Endian::toString4(string& text, unsigned char* pBuffer) {
	char*	pText((char*) pBuffer);

	text = {pText[0], pText[1], pText[2], pText[3]};
}

//-----------------------------------------------------------------------------
void Endian::toStringN(string& text, unsigned char* pBuffer, size_t length) {
	text.assign((char*) pBuffer, length);
}

//-----------------------------------------------------------------------------
void Endian::toSizeT(size_t& value, unsigned char* pBuffer) {
	value = (pBuffer[3] << 24) | (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toULong(unsigned long& value, unsigned char* pBuffer) {
	value = (pBuffer[3] << 24) | (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toLong(long& value, unsigned char* pBuffer) {
	value = (pBuffer[3] << 24) | (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toLong8(long& value, unsigned char* pBuffer) {
	value   = (pBuffer[7] << 24) | (pBuffer[6] << 16) | (pBuffer[5] << 8) | pBuffer[4];
	value <<= 32;
	value  |= (pBuffer[3] << 24) | (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toUShort(unsigned short& value, unsigned char* pBuffer) {
	value = (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toShort(short& value, unsigned char* pBuffer) {
	value = (pBuffer[1] << 8) | pBuffer[0];
}

//-----------------------------------------------------------------------------
void Endian::toFloat4(float& value, unsigned char* pBuffer) {
	value = *((float*) pBuffer);
}

//-----------------------------------------------------------------------------
void Endian::toHash4(unsigned long& value, unsigned char* pBuffer) {
	value = (pBuffer[0] << 24) | (pBuffer[1] << 16) | (pBuffer[2] << 8) | pBuffer[3];
}

//-----------------------------------------------------------------------------
void Endian::toChar(unsigned char& text, unsigned char* pBuffer) {
	text = pBuffer[0];
}
