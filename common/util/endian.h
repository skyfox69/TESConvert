#ifndef ENDIAN_H
#define	ENDIAN_H

#include <string>

using namespace std;

//-----------------------------------------------------------------------------
class Endian
{
	protected:
		void	toString4(string& text, unsigned char* pBuffer);
		void	toStringN(string& text, unsigned char* pBuffer, size_t length);
		void	toSizeT  (size_t& value, unsigned char* pBuffer);
		void	toULong  (unsigned long& value, unsigned char* pBuffer);
		void	toLong   (long& value, unsigned char* pBuffer);
		void	toLong8  (long& value, unsigned char* pBuffer);
		void	toUShort (unsigned short& value, unsigned char* pBuffer);
		void	toShort  (short& value, unsigned char* pBuffer);
		void	toFloat4 (float& value, unsigned char* pBuffer);
		void	toHash4  (unsigned long& value, unsigned char* pBuffer);
		void	toChar   (unsigned char& text, unsigned char* pBuffer);
};

#endif	/* ENDIAN_H */

