#include "stdafx.h"
#include "EXSQLiteQueryObject.h"

#include "sqlite3.h"
#include <assert.h>

CEXSQLiteQueryObject::CEXSQLiteQueryObject()
	: m_bEof( true )
	, m_pSqlite( NULL )
	, m_pStmt( NULL )
	, m_colNum( 0 )
{
}

CEXSQLiteQueryObject::~CEXSQLiteQueryObject()
{
	Detach();
}


void CEXSQLiteQueryObject::Attach( sqlite3* psqlite, sqlite3_stmt* pstmt )
{
	Detach();
	assert( NULL != psqlite && NULL != pstmt );

	m_pSqlite = psqlite;
	m_pStmt = pstmt;
	m_bEof = false;

	m_colNum = sqlite3_column_count( pstmt );
}

void CEXSQLiteQueryObject::Detach()
{
	if ( NULL != m_pSqlite && NULL != m_pStmt )
	{
		int ret = sqlite3_finalize( m_pStmt );

		m_pStmt = NULL;
		m_pSqlite = NULL;
	}
}


bool CEXSQLiteQueryObject::Step()
{
	assert( NULL != m_pSqlite && NULL != m_pStmt );

	if ( m_bEof )
	{
		return false;
	}

	int ret = sqlite3_step( m_pStmt );

	m_bEof = ( SQLITE_ROW == ret ? false : true );

	return !m_bEof;
}

int CEXSQLiteQueryObject::GetFieldIndex( const EXString& strFieldName )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	for( int index = 0; index < m_colNum; ++index )
	{
		EXString strName = sqlite3_column_name( m_pStmt, index );
		if ( strName == strFieldName )
		{
			return index;
		}
	}

	assert( 0 );

	return -1;
}

bool CEXSQLiteQueryObject::GetFieldName( int nField, EXString& strFieldName )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert(( nField >= 0  && ( nField < m_colNum )));

	strFieldName = sqlite3_column_name( m_pStmt, nField );

	return true;
}

int CEXSQLiteQueryObject::GetFieldDataType( int nField )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert(( nField >= 0  && ( nField < m_colNum )));

	return sqlite3_column_type( m_pStmt, nField );

}

bool CEXSQLiteQueryObject::GetFieldDeclType( int nField, EXString& strFieldName )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	strFieldName = sqlite3_column_decltype( m_pStmt, nField );

	return true;
}

bool CEXSQLiteQueryObject::GetFieldInt64( int nField, INT64& val )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	val = sqlite3_column_int64( m_pStmt, nField );

	return true;
}

bool CEXSQLiteQueryObject::GetFieldFloat64( int nField, DOUBLE& val )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert( ( nField >= 0  && ( nField < m_colNum )));

	val = sqlite3_column_double( m_pStmt, nField );

	return true;
}

bool CEXSQLiteQueryObject::GetFieldString( int nField, EXString& val )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );

	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	const unsigned char* ret = sqlite3_column_text( m_pStmt, nField );
	assert( NULL != ret );

	val = (const char*)ret;

	return true;
}

bool CEXSQLiteQueryObject::GetFieldString( int nField, CEXDataBlob& blob )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );
	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	int len  = sqlite3_column_bytes(m_pStmt, nField);
	const unsigned char* data = sqlite3_column_text(m_pStmt, nField);
	if (data != NULL)
	{
		blob.m_data = new char[len];
		blob.m_length = len;

		memcpy_s( blob.m_data, blob.m_length, data, len);
	}
	else
	{
		blob.m_data = NULL;
		blob.m_length = 0;	
	}

	return true;
}

bool CEXSQLiteQueryObject::GetFieldBlob( int nField, EXString& blob )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );
	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	int len = sqlite3_column_bytes(m_pStmt, nField);
	const void* data = sqlite3_column_blob(m_pStmt, nField);
	if (data != NULL)
	{
		blob.resize(len);
		memcpy_s( (char*)blob.c_str(), len, data, len);
	}

	return true;
}

bool CEXSQLiteQueryObject::GetFieldBlob( int nField, CEXDataBlob& blob )
{
	assert( NULL != m_pStmt && NULL != m_pSqlite );
	assert( ( nField >= 0  && ( nField < m_colNum )));

	if ( IsNull( nField ) )
	{
		return false;
	}

	int len  = sqlite3_column_bytes(m_pStmt, nField);
	const void* data = sqlite3_column_blob(m_pStmt, nField);
	if (data != NULL)
	{
		blob.m_data = new char[len];
		blob.m_length = len;

		memcpy_s( blob.m_data, blob.m_length, data, len);
	}
	else
	{
		blob.m_data = NULL;
		blob.m_length = 0;	
	}

	return true;
}


bool CEXSQLiteQueryObject::IsNull( int nField )
{
	int sqlitetype = sqlite3_column_type( m_pStmt, nField );

	return SQLITE_NULL == sqlitetype;
}
