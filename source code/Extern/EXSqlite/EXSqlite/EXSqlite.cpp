// EXSqlite.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EXSqlite.h"
#include "EXStringConvert/EXStringConvert.h"
#include "EXSQLiteQueryObject.h"
#include "EXSQLiteExecuteObject.h"
#include "sqlite3.h"

#include <assert.h>

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 EXSqlite.h
CEXSqlite::CEXSqlite()
{
	return;
}

CEXSqlite::~CEXSqlite()
{

}

bool CEXSqlite::Connect( const char* szDBName, unsigned int flags /*= SQ_OPEN_READ */ )
{
	assert( NULL != szDBName );

	if ( IsConnected() )
	{
		return true;
	}

	int openFlags = 0;
	if (flags == SQ_OPEN_READ)
	{
		openFlags = SQLITE_OPEN_READONLY | SQLITE_OPEN_SHAREDCACHE;
	}
	else if (flags == SQ_OPEN_WRITE)
	{
		openFlags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_SHAREDCACHE;
	}
	else
	{
		assert(0);
		return false;
	}

	// translate szDBName to utf-8 encode
	std::string strTemp( szDBName );
	m_dbName = strTemp;
	strTemp = EX_STRING::AsciiToUtf8( szDBName );

	int ret = sqlite3_open_v2( strTemp.c_str(), &m_pSqlite, openFlags, NULL );

	if ( SQLITE_OK != ret )
	{
		sqlite3_close( m_pSqlite );

		m_pSqlite = NULL;
		return false;
	}

	return true;
}

void CEXSqlite::DisConnect()
{
	if ( NULL != m_pSqlite )
	{
		int backtime = 5;

		do 
		{
			int ret = sqlite3_close( m_pSqlite );
			if ( ret == SQLITE_OK )
			{
				break;
			}

			::Sleep(10);
			--backtime;
		} while ( backtime );

		m_pSqlite = NULL;
	}
}

bool CEXSqlite::ExecuteSQL( const char* szSql )
{
	assert( NULL != szSql && NULL != m_pSqlite );

	int ret = sqlite3_exec( m_pSqlite, szSql, 0, 0, NULL );

	return ( SQLITE_OK == ret ? true : false );
}

bool CEXSqlite::ExecuteSQL( const char* szSql, CEXSQLiteExecuteObject& execute )
{
	assert( NULL != szSql && NULL != m_pSqlite );

	sqlite3_stmt* pstmt = ComplieSQL(szSql);
	if ( NULL == pstmt )
	{
		return false;
	}

	execute.Attach( m_pSqlite, pstmt );

	return true;
}

bool CEXSqlite::ExecuteQuerySQL( const char* szSql, CEXSQLiteQueryObject& pquery )
{
	assert( NULL != szSql && NULL != m_pSqlite );

	sqlite3_stmt* pstmt = ComplieSQL(szSql);
	if ( NULL == pstmt )
	{
		return false;
	}

	pquery.Attach( m_pSqlite, pstmt );

	return true;
}

struct sqlite3_stmt* CEXSqlite::ComplieSQL( const char* szSql )
{
	assert( NULL != szSql && NULL != m_pSqlite );

	sqlite3_stmt* pstmt = NULL;
	const char* szTail = NULL;

	int ret = sqlite3_prepare_v2( m_pSqlite, szSql, -1, &pstmt, &szTail );

	if ( SQLITE_OK != ret )
	{
		return NULL;
	}

	return pstmt;
}

bool CEXSqlite::BeginTransactions( unsigned int model /*= TRANSACTION_DEFERRED */ )
{
	if ( !m_bCommitTransaction )
	{
		return false;
	}

	EXString sqlStr;
	switch( model )
	{
	case TRANSACTION_DEFERRED:
		sqlStr = "begin deferred";
		break;

	case TRANSACTION_IMMEDIATE:
		sqlStr = "begin immediate";
		break;

	case TRANSACTION_EXCLUSIVE:
		sqlStr = "begin exclusive";
		break;

	default:
		assert( 0 );
		return false;
	}

	m_bCommitTransaction = false;

	return ExecuteSQL( sqlStr.c_str() );
}

bool CEXSqlite::CommitTransactions()
{
	if ( !m_bCommitTransaction )
	{
		m_bCommitTransaction = true;
		return ExecuteSQL( "commit" );
	}

	return false;
}

bool CEXSqlite::SetWALMode()
{
	return ExecuteSQL( "PRAGMA journal_mode = WAL;" );
}
