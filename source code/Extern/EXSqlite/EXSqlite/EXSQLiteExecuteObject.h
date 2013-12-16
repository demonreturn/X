#pragma once

#include "EXTypeDefine.h"

struct sqlite3;
struct sqlite3_stmt;
class CEXSqlite;

class CEXSQLiteExecuteObject
{
	friend class CEXSqlite;

public:
	CEXSQLiteExecuteObject();
	~CEXSQLiteExecuteObject();

	bool Execute();

	/*
		注意： pos从0开始
	*/
	void BindNull(int pos);
	void BindInt(int pos, int val);
	void BindInt64(int pos, INT64 val);
	void BindFloat32(int pos, FLOAT val);
	void BindFloat64(int pos, DOUBLE val);
	void BindString(int pos, const char* str, int length);
	void BindBlob(int pos, const void* data, int length);

private:
	void Attach(struct sqlite3* psqlite, struct sqlite3_stmt* pstmt );
	void Detach();

private:
	struct sqlite3*				m_pSqlite;
	struct sqlite3_stmt*		m_pStmt;
};

