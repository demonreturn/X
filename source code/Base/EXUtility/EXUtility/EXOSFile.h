#pragma once

#include "EXUtilityDefine.h"
#include "EXTypeDefine.h"

#include <fcntl.h>

namespace EXOS
{
	/*
	 * function desc: 打开文件
	 *
	 * [param] [IN]/[OUT]： 
	 * pszFilePath		[IN]	: 文件全路径
	 * dwFlags			[IN]	 : O_RDONLY, O_WRONLY or O_RDWR,|  O_CREAT() O_TRUNC   O_APPEND
	 * dwFileModel		[IN]	 : FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE
	 * pSecrtity		[IN]	 : 
	 * 
	 * [Return]
	 * 成功返回文件句柄，失败 -1 
	 */

	extern EX_API HANDLE OpenFile( 
		const char* pszFilePath,
		DWORD dwFlags = O_RDONLY,
		DWORD dwFileModel = FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
		DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL,
		LPSECURITY_ATTRIBUTES pSecrtity = NULL );
	
	/*
	 * function desc: 读取文件
	 *
	 * [param] [IN]/[OUT]： 
	 * fileHandle		[IN]	 : 文件句柄
	 * pBuffer			[OUT]	 :
	 * [return]
	 *
	 */

	extern EX_API INT32 ReadFile(
		HANDLE fileHandle,
		LPVOID pBuffer,
		DWORD dwReadSize,
		LPDWORD dwHaveRead );

	extern EX_API INT32 WriteFile( 
		HANDLE fileHandle,
		const LPVOID pBuffer,
		DWORD dwWriteSize,
		LPDWORD dwHaveWrite );

	extern EX_API INT32 SeekFile(
		HANDLE fileHandle,
		LONGLONG llDistance,
		DWORD dwMoveMethod );

	extern EX_API INT32 FlushFile( HANDLE fileHandle );

	extern EX_API INT32 CloseFile( HANDLE fileHandle );

	extern EX_API LONGLONG GetCurSeekPos( HANDLE fileHandle );

	extern EX_API INT32 GetFileAttribute(
		const char* pfilePath,
		FileAttribute* fileAttribute );

	extern EX_API INT32 ReadLockFile(
		HANDLE fileHandle,
		LONGLONG offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY );

	extern EX_API INT32 WriteLockFile(
		HANDLE fileHandle,
		LONGLONG offset,
		LONGLONG llLockSize );

	extern EX_API INT32 UnLockFile(
		HANDLE fileHandle,
		LONGLONG offset,
		LONGLONG llLockSize );

	extern EX_API INT32 IsFileExist( const char* pFilePath );

	extern EX_API INT32 DeleteFile( const char* pFilePath );

	extern EX_API INT32 GetDiskFreeSpace( const char* pPath );

	extern EX_API INT32 TruncateFile(
		HANDLE fileHandle,
		LONGLONG llSize );

	extern EX_API INT32 CopyFile( 
		const char* pSourceFile,
		const char* pDestFile,
		bool bFailIfExist = true );
}