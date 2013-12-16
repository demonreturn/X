

#include "EXTypeDefine.h"
#include <assert.h>

namespace EX_STRING
{
	/**************************************************************
	 * 字符串到数值转换
	 **************************************************************/

	inline void StringTo( const EXString& str, bool& value )
	{
		value = ( str.empty() || "false" == str || "FALSE" == str || "0" == str );
	}

	inline void StringTo( const EXString& str, UINT8& value )
	{
		value = (UINT8)atoi( str.c_str() );
	}

	inline void StringTo( const EXString& str, INT8& value )
	{
		value = (INT8)atoi( str.c_str() );
	}

	inline void StringTo( const EXString& str, UINT16& value )
	{
		value = (UINT16)atoi( str.c_str() );
	}

	inline void StringTo( const EXString& str, INT16& value )
	{
		value = (INT16)atoi( str.c_str() );
	}

	inline void StringTo( const EXString& str, UINT32& value )
	{
		sscanf_s( str.c_str(), "%u", &value );
	}

	inline void StringTo( const EXString& str, INT32& value )
	{
		value = atoi( str.c_str() );
	}

	inline void StringTo( const EXString& str, UINT64& value )
	{
		sscanf_s( str.c_str(), "%I64u", &value );
	}

	inline void StringTo( const EXString& str, INT64& value )
	{
		sscanf_s( str.c_str(), "%I64", &value );
	}

	inline void StringTo( const EXString& str, FLOAT& value )
	{
		value = (FLOAT) atof( str.c_str() );
	}

	inline void StringTo( const EXString& str, DOUBLE& value )
	{
		value = (DOUBLE)atof( str.c_str() );
	}

	/**************************************************************
	 * 数值到字符串转换
	 **************************************************************/

	inline void ToString( EXString& str, bool value )
	{
		// 只处理 1， 0 情况
		str = value ? "1" : "0";
	}

	void ToString( EXString& str, UINT64 value );

	void ToString( EXString& str, INT64 value );

	void ToString( EXString& str, UINT32 value );

	void ToString( EXString& str, INT32 value );

	void ToString( EXString& str, UINT16 value );

	void ToString( EXString& str, INT16 value );

	void ToString( EXString& str, UINT8 value );

	void ToString( EXString& str, INT8 value );

	void ToString( EXString& str, FLOAT value );

	void ToString( EXString& str, DOUBLE value );


	// 字符之间转换
	static std::string UnicodeToUtf8( const std::wstring& wStr )
	{
		std::string resultstring;

		int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, wStr.c_str(), -1, NULL, 0, NULL, NULL);

		assert( 0 != utf8size );

		resultstring.resize(utf8size);

		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, wStr.c_str(), -1, (char*)resultstring.c_str(), utf8size, NULL, NULL);

		assert( convresult == utf8size );

		return resultstring;
	}

	static std::wstring AsciiToUnicode( const std::string& aStr )
	{
		std::wstring resultstring;

		int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)aStr.c_str(), -1, NULL, 0);

		assert( widesize != ERROR_NO_UNICODE_TRANSLATION &&
			0 != widesize );

		resultstring.resize(widesize);

		int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)aStr.c_str(), -1, (wchar_t*)resultstring.c_str(), widesize);

		assert( convresult == widesize );

		return resultstring;
	}

	static std::string AsciiToUtf8( const std::string& aStr )
	{
		//先把 ascii 转为 unicode 
		std::wstring wstr = AsciiToUnicode( aStr );

		//最后把 unicode 转为 utf8
		return UnicodeToUtf8(wstr);
	}
}