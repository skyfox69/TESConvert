#ifndef ENDIAN_H
#define	ENDIAN_H

#include <string>

using namespace std;

//-----------------------------------------------------------------------------
class Endian
{
	protected:
		//  memory => attribute
		virtual	void	toString4(string& text, unsigned char* pBuffer);
		virtual	void	toStringN(string& text, unsigned char* pBuffer, size_t length);
		virtual	void	toSizeT  (size_t& value, unsigned char* pBuffer);
		virtual	void	toULong  (unsigned long& value, unsigned char* pBuffer);
		virtual	void	toLong   (long& value, unsigned char* pBuffer);
		virtual	void	toLong8  (long& value, unsigned char* pBuffer);
		virtual	void	toUShort (unsigned short& value, unsigned char* pBuffer);
		virtual	void	toUShort4(unsigned long& value, unsigned char* pBuffer);
		virtual	void	toShort  (short& value, unsigned char* pBuffer);
		virtual	void	toFloat4 (float& value, unsigned char* pBuffer);
		virtual	void	toHash4  (unsigned long& value, unsigned char* pBuffer);
		virtual	void	toChar   (unsigned char& text, unsigned char* pBuffer);

		//  attribute => file
		virtual	void	writeString4(const string text, FILE* pFile);
		virtual	void	writeStringN(const string text, FILE* pFile);
		virtual	void	writeSizeT  (const size_t value, FILE* pFile);
		virtual	void	writeULong  (const unsigned long value, FILE* pFile);
		virtual	void	writeLong   (const long value, FILE* pFile);
		virtual	void	writeUShort4(const unsigned long value, FILE* pFile);
		virtual	void	writeUShort (const unsigned short value, FILE* pFile);
		virtual	void	writeShort  (const short value, FILE* pFile);
		virtual	void	writeFloat4 (const float value, FILE* pFile);
		virtual	void	writeChar   (const unsigned char value, FILE* pFile);

		//  attribute => memory
		virtual	size_t	writeString4(const string text, unsigned char* pMemory);
		virtual	size_t	writeUShort4(const unsigned long value, unsigned char* pMemory);
		virtual	size_t	writeUShort (const unsigned short value, unsigned char* pMemory);
		virtual	size_t	writeULong  (const unsigned long value, unsigned char* pMemory);
		virtual	size_t	writeFloat4 (const float value, unsigned char* pMemory);
		virtual	size_t	writeSizeT  (const size_t value, unsigned char* pMemory);
};

#endif	/* ENDIAN_H */

