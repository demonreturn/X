#include "EXOSFile.h"


extern EX_API HANDLE EXOS::OpenFile( 
	const char* pszFilePath,
	DWORD dwFlags /*= O_RDONLY*/,
	DWORD dwFileModel /*= FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE*/,
	DWORD dwFileAttributes /*= FILE_ATTRIBUTE_NORMAL*/,
	LPSECURITY_ATTRIBUTES pSecrtity /*= NULL */ )
{
	DWORD dwAccess = GENERIC_READ;
	DWORD dwShareMode = dwFileModel;
	DWORD dwCreation = OPEN_EXISTING;
	DWORD dwFlagsAndAttributes = dwFileAttributes;

	//对文件的访问权限标志
	if ( EX_BIT_ENABLED( dwFlags, O_WRONLY ) )
	{
		dwAccess = GENERIC_WRITE;
	}
	else if ( EX_BIT_ENABLED( dwFlags, O_RDWR ) )
	{
		dwAccess = GENERIC_READ | GENERIC_WRITE;
	}
	//文件打开/创建标志
	if ( EX_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_EXCL ), ( O_CREAT | O_EXCL ) ) )
		//if ( (nFlags & (_O_CREAT | _O_EXCL) ) == (_O_CREAT | _O_EXCL) )
	{
		//文件不存在,生成一个新文件
		//文件已存在,创建失败
		dwCreation = CREATE_NEW;
	}
	else if( EX_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_TRUNC ), ( O_CREAT | O_TRUNC ) ) )
		//else if ( (nFlags & (_O_CREAT | _O_TRUNC) ) == ((_O_CREAT | _O_TRUNC)) )
	{
		//文件已存在,返回成功 文件被清空
		//文件不存在,生成一个新文件
		dwCreation = CREATE_ALWAYS;
	}
	else if ( EX_BIT_ENABLED (dwFlags, O_CREAT) )
	{
		//文件已存在,返回成功
		//文件不存在,生成一个新文件
		dwCreation = OPEN_ALWAYS;
	}
	else if ( EX_BIT_ENABLED (dwFlags, O_TRUNC) )
	{
		//文件不存在,返回失败
		dwCreation = TRUNCATE_EXISTING;
	}

	if ( EX_BIT_ENABLED( dwFlags, O_TEMPORARY ) )
	{
		//临时文件属性
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE;
	}

	HANDLE handle = ::CreateFile(
		pszFilePath,
		dwAccess,
		dwShareMode,
		pSecrtity,
		dwCreation,
		dwFlagsAndAttributes,
		NULL );

	if ( INVALID_HANDLE_VALUE == handle )
	{
		return handle;
	}
	else
	{
		if ( EX_BIT_ENABLED( dwFlags, O_APPEND) )
		{
			::SetFilePointer( handle,
				0,
				0,
				FILE_END );
		}

		return handle;
	}

	return NULL;
}

extern EX_API INT32 EXOS::ReadFile( 
	HANDLE fileHandle,
	LPVOID pBuffer,
	DWORD dwReadSize,
	LPDWORD dwHaveRead )
{

}
