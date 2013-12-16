// EXStringConvert.cpp : 定义 DLL 应用程序的导出函数。
//


#include "EXStringConvert/EXStringConvert.h"


namespace Detail
{
	static const char s_digits[] = "9876543210123456789";
	static const char* s_zero = s_digits + 9;
	static const char s_digitsHex[] = "0123456789ABCEDF";

	template< typename type >
	size_t convert( char buff[], type value )
	{
		type v = value;
		char* p = buff;

		do 
		{
			INT32 lsd = static_cast<INT32>( v % 10 );
			v /= 10;
			*p++ = s_zero[lsd];
		} while ( v != 0 );

		if ( v < 0 )
		{
			*p++ = '-';
		}

		*p = '\0';
		std::reverse( buff, p );

		return p - buff;
	}

	size_t convertHex(char buf[],  ULONG value)
	{
		ULONG i = value;
		char* p = buf;

		do
		{
			int lsd = i % 16;
			i /= 16;
			*p++ = s_digitsHex[lsd];
		} while (i != 0);

		*p = '\0';
		std::reverse(buf, p);

		return p - buf;
	}

	static inline INT Sprintf(
		char *buffer,
		size_t sizeOfBuffer,
		const char *format,
		... )
	{
		va_list argp;
		va_start (argp, format);
		int result = ::_vsprintf_s_l(
			buffer, 
			sizeOfBuffer, 
			format, 
			NULL, 
			argp );

		va_end( argp );
		return result;
	}
}

void EX_STRING::ToString( EXString& str, UINT64 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, INT64 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, UINT32 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, INT32 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, UINT16 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, INT16 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, UINT8 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, INT8 value )
{
	char buf[32] = {0};
	Detail::convert( buf, value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, FLOAT value )
{
	char buf[32] = {0};
	Detail::Sprintf( buf, 32, "%.4f", value );

	str = buf;
}

void EX_STRING::ToString( EXString& str, DOUBLE value )
{
	char buf[32] = {0};
	Detail::Sprintf( buf, 32, "%.12g", value );

	str = buf;
}
