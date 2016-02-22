#include "common/util/endian.h"
#include <cstring>

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
void Endian::toUShort4(unsigned long& value, unsigned char* pBuffer) {
	value = 0;
	value |= (pBuffer[1] << 8) | pBuffer[0];
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

//-----------------------------------------------------------------------------
void Endian::writeString4(const string text, FILE* pFile) {
	fwrite(text.c_str(), 1, 4, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeStringN(const string text, FILE* pFile) {
	unsigned char	empty(0);

	fwrite(text.c_str(), 1, text.size(), pFile);
	fwrite(&empty, 1, 1, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeSizeT(const size_t value, FILE* pFile) {
	unsigned char	buffer[4] = {0};

	buffer[0] = (value & 0x000000FF);
	buffer[1] = (value & 0x0000FF00) >> 8;
	buffer[2] = (value & 0x00FF0000) >> 16;
	buffer[3] = (value & 0xFF000000) >> 24;
	fwrite(buffer, 1, 4, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeUShort4(const unsigned long value, FILE* pFile) {
	unsigned char	buffer[4] = {0};

	buffer[0] = (value & 0x000000FF);
	buffer[1] = (value & 0x0000FF00) >> 8;
	fwrite(buffer, 1, 2, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeUShort(const unsigned short value, FILE* pFile) {
	unsigned char	buffer[2] = {0};

	buffer[0] = (value & 0x00FF);
	buffer[1] = (value & 0xFF00) >> 8;
	fwrite(buffer, 1, 2, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeShort(const short value, FILE* pFile) {
	unsigned char	buffer[2] = {0};

	buffer[0] = (value & 0x00FF);
	buffer[1] = (value & 0xFF00) >> 8;
	fwrite(buffer, 1, 2, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeULong(const unsigned long value, FILE* pFile) {
	unsigned char	buffer[4] = {0};

	buffer[0] = (value & 0x000000FF);
	buffer[1] = (value & 0x0000FF00) >> 8;
	buffer[2] = (value & 0x00FF0000) >> 16;
	buffer[3] = (value & 0xFF000000) >> 24;
	fwrite(buffer, 1, 4, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeLong(const long value, FILE* pFile) {
	unsigned char	buffer[4] = {0};

	buffer[0] = (value & 0x000000FF);
	buffer[1] = (value & 0x0000FF00) >> 8;
	buffer[2] = (value & 0x00FF0000) >> 16;
	buffer[3] = (value & 0xFF000000) >> 24;
	fwrite(buffer, 1, 4, pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeFloat4(const float value, FILE* pFile) {
	fwrite(&value, 1, sizeof(float), pFile);
}

//-----------------------------------------------------------------------------
void Endian::writeChar(const unsigned char value, FILE* pFile) {
	fwrite(&value, 1, 1, pFile);
}

//-----------------------------------------------------------------------------
size_t Endian::writeString4(const string text, unsigned char* pMemory) {
	memcpy(pMemory, text.c_str(), 4);
	return 4;
}

//-----------------------------------------------------------------------------
size_t Endian::writeUShort4(const unsigned long value, unsigned char* pMemory) {
	pMemory[0] = (value & 0x000000FF);
	pMemory[1] = (value & 0x0000FF00) >> 8;
	return 2;
}

//-----------------------------------------------------------------------------
size_t Endian::writeULong(const unsigned long value, unsigned char* pMemory) {
	pMemory[0] = (value & 0x000000FF);
	pMemory[1] = (value & 0x0000FF00) >> 8;
	pMemory[2] = (value & 0x00FF0000) >> 16;
	pMemory[3] = (value & 0xFF000000) >> 24;
	return 4;
}

//-----------------------------------------------------------------------------
size_t Endian::writeFloat4(const float value, unsigned char* pMemory) {
	memcpy(pMemory, &value, 4);
	return 4;
}

//-----------------------------------------------------------------------------
size_t Endian::writeSizeT(const size_t value, unsigned char* pMemory) {
	pMemory[0] = (value & 0x000000FF);
	pMemory[1] = (value & 0x0000FF00) >> 8;
	pMemory[2] = (value & 0x00FF0000) >> 16;
	pMemory[3] = (value & 0xFF000000) >> 24;
	return 4;
}

//-----------------------------------------------------------------------------
size_t Endian::writeUShort(const unsigned short value, unsigned char* pMemory) {
	pMemory[0] = (value & 0x00FF);
	pMemory[1] = (value & 0xFF00) >> 8;
	return 2;
}

