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

	//���ļ��ķ���Ȩ�ޱ�־
	if ( EX_BIT_ENABLED( dwFlags, O_WRONLY ) )
	{
		dwAccess = GENERIC_WRITE;
	}
	else if ( EX_BIT_ENABLED( dwFlags, O_RDWR ) )
	{
		dwAccess = GENERIC_READ | GENERIC_WRITE;
	}
	//�ļ���/������־
	if ( EX_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_EXCL ), ( O_CREAT | O_EXCL ) ) )
		//if ( (nFlags & (_O_CREAT | _O_EXCL) ) == (_O_CREAT | _O_EXCL) )
	{
		//�ļ�������,����һ�����ļ�
		//�ļ��Ѵ���,����ʧ��
		dwCreation = CREATE_NEW;
	}
	else if( EX_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_TRUNC ), ( O_CREAT | O_TRUNC ) ) )
		//else if ( (nFlags & (_O_CREAT | _O_TRUNC) ) == ((_O_CREAT | _O_TRUNC)) )
	{
		//�ļ��Ѵ���,���سɹ� �ļ������
		//�ļ�������,����һ�����ļ�
		dwCreation = CREATE_ALWAYS;
	}
	else if ( EX_BIT_ENABLED (dwFlags, O_CREAT) )
	{
		//�ļ��Ѵ���,���سɹ�
		//�ļ�������,����һ�����ļ�
		dwCreation = OPEN_ALWAYS;
	}
	else if ( EX_BIT_ENABLED (dwFlags, O_TRUNC) )
	{
		//�ļ�������,����ʧ��
		dwCreation = TRUNCATE_EXISTING;
	}

	if ( EX_BIT_ENABLED( dwFlags, O_TEMPORARY ) )
	{
		//��ʱ�ļ�����
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
