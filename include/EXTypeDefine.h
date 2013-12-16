
#pragma once

#include <string>
#include <vector>
#include <list>

#include <windows.h>

// �������Ͷ���
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

// �����ַ������Ͷ���
typedef std::string					EXString;
typedef std::vector<EXString>		EXStringVector;
typedef std::list<EXString>			EXStringList;

// ����ʱ�����Ͷ�һ��
typedef INT32						TIME32_S;		// ����Ϊ���ȵ�ʱ��,32λ
typedef INT64						TIME64_S;		// ����Ϊ���ȵ�ʱ��,64λ
typedef	INT64						TIME64_MS;		// �Ժ���Ϊ��λ

// ����ֵ���Ͷ���
typedef long						EXResult;


// ƽ̨�������Ͷ���
typedef struct tag_fileAttributes
{
	LONGLONG					llFileSize;
	TIME64_MS					llCreateTime;
	TIME64_MS					llModifyTime;
} FileAttribute;
