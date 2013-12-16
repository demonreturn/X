#include "stdafx.h"
#include "EXSQLiteExecuteObject.h"
#include "sqlite3.h"

#include <assert.h>

CEXSQLiteExecuteObject::CEXSQLiteExecuteObject()
	: m_pSqlite( NULL )
	, m_pStmt( NULL )
{
}

CEXSQLiteExecuteObject::~CEXSQLiteExecuteObject()
{
	Detach();
}

bool CEXSQLiteExecuteObject::Execute()
{
	assert( NULL != m_pSqlite && NULL != m_pStmt );

	int ret = sqlite3_step( m_pStmt );

	return ( SQLITE_DONE == ret);
}

void CEXSQLiteExecuteObject::Attach( struct sqlite3* psqlite, struct sqlite3_stmt* pstmt )
{
	assert( NULL != psqlite && NULL != pstmt );

	Detach();	

	m_pSqlite = psqlite;
	m_pStmt = pstmt;
}

void CEXSQLiteExecuteObject::Detach()
{
	if ( NULL != m_pSqlite && NULL != m_pStmt )
	{
		int ret = sqlite3_finalize( m_pStmt );

		m_pStmt = NULL;
		m_pSqlite = NULL;
	}
}

void CEXSQLiteExecuteObject::BindInt( int pos, int val )
{
	sqlite3_bind_int(m_pStmt, pos+1, val); // pos 从0开始计数，而bind实际上从1开始计数
}

void CEXSQLiteExecuteObject::BindInt64( int pos, INT64 val )
{
	sqlite3_bind_int64(m_pStmt, pos+1, val);
}

void CEXSQLiteExecuteObject::BindFloat32( int pos, FLOAT val )
{
	sqlite3_bind_double(m_pStmt, pos+1, val);
}

void CEXSQLiteExecuteObject::BindFloat64( int pos, DOUBLE val )
{
	sqlite3_bind_double(m_pStmt, pos+1, val);
}

void CEXSQLiteExecuteObject::BindString( int pos, const char* str, int length )
{
	sqlite3_bind_text(m_pStmt, pos+1, str, length, NULL);
}

void CEXSQLiteExecuteObject::BindBlob( int pos, const void* data, int length )
{
	sqlite3_bind_blob(m_pStmt, pos+1, data, length, NULL);
}

void CEXSQLiteExecuteObject::BindNull( int pos )
{
	sqlite3_bind_null(m_pStmt, pos+1);
}
