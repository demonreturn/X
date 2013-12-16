
#pragma once

#include <string>
#include <vector>
#include <list>

#include <windows.h>

// 数据类型定义
typedef short						SHORT;
typedef __int16						INT16;
typedef unsigned __int16			UINT16;
typedef __int32						INT32;
typedef unsigned __int32			UINT32;
typedef __int64						INT64;
typedef unsigned __int64			UINT64;
typedef long						LONG;
typedef long long					LONGLONG;
typedef unsigned long				ULONG;
typedef unsigned long long			ULONGLONG;
typedef float						FLOAT;
typedef double						DOUBLE;
typedef __int32						BOOL;
typedef char						CHAR;
typedef char						TCHAR;
typedef unsigned char				BYTE;

// 常用字符串类型定义
typedef std::string					EXString;
typedef std::vector<EXString>		EXStringVector;
typedef std::list<EXString>			EXStringList;

// 常用时间类型顶一个
typedef INT32						TIME32_S;		// 以秒为精度的时间,32位
typedef INT64						TIME64_S;		// 以秒为精度的时间,64位
typedef	INT64						TIME64_MS;		// 以毫秒为单位

// 返回值类型定义
typedef long						EXResult;


// 平台差异类型定义
typedef struct tag_fileAttributes
{
	LONGLONG					llFileSize;
	TIME64_MS					llCreateTime;
	TIME64_MS					llModifyTime;
} FileAttribute;
