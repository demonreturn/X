#pragma once

#include "EXTypeDefine.h"

class CEXDataBlob
{
public:
	char*		m_data;
	unsigned	m_length;
};

class CEXSQLiteQueryObject
{
	friend class CEXSqlite;

public:
	CEXSQLiteQueryObject();
	~CEXSQLiteQueryObject();

public:
	int GetFieldCount() const
	{
		return m_colNum;
	}

	bool Eof() const
	{
		return m_bEof;
	}


	int GetFieldIndex( const EXString& strFieldName );
	bool GetFieldName( int nField, EXString& strFieldName );

	int GetFieldDataType( int nField );
	bool GetFieldDeclType( int nField, EXString& strFieldName );

public:

	bool Step();

	bool GetFieldInt64( int nField, INT64& val );

	bool GetFieldFloat64( int nField, DOUBLE& val );

	bool GetFieldString( int nField, EXString& val );
	bool GetFieldString( int nField, CEXDataBlob& val );

	bool GetFieldBlob( int nField, EXString& blob );
	bool GetFieldBlob( int nField, CEXDataBlob& blob );

private:
	void Attach(struct sqlite3* psqlite, struct sqlite3_stmt* pstmt );

	void Detach();

	bool IsNull( int nField );
private:
	bool						m_bEof;
	struct sqlite3*				m_pSqlite;
	struct sqlite3_stmt*		m_pStmt;
	int							m_colNum;
};

