// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 EXSQLITE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// EXSQLITE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef EXSQLITE_EXPORTS
#define EXSQLITE_API __declspec(dllexport)
#else
#define EXSQLITE_API __declspec(dllimport)
#endif

#include "EXTypeDefine.h"

struct sqlite3_stmt;
struct sqlite3;
class CEXSQLiteQueryObject;
class CEXSQLiteExecuteObject;

// 此类是从 EXSqlite.dll 导出的
class EXSQLITE_API CEXSqlite 
{
public:
	enum FLAG
	{
		SQ_OPEN_READ = 0x01,
		SQ_OPEN_WRITE= 0x01 << 1
	};

	/*
	 * 事务模式：
	 * TRANSACTION_DEFERRED		：启动时，并不加锁数据库，第一次出现修改数据库操作时，会加锁数据库，此时只有一个写连接
	 *							 可以有多个读连接
	 * TRANSACTION_DEFERRED		：启动成功时，加锁数据库，并保证没有其他写数据库连接，只有一个写连接。，可以有多个读连接
	 * TRANSACTION_EXCLUSIVE	：启动成功时，保证只有一个连接，并没有其他连接。
	 */
	enum TRANS_MODEL
	{
		TRANSACTION_DEFERRED	= 0x01,
		TRANSACTION_IMMEDIATE	= 0x01 << 1,
		TRANSACTION_EXCLUSIVE	= 0x01 << 2
	};

public:
	CEXSqlite();
	~CEXSqlite();

public:

	bool Connect(
		const char* szDBName,
		unsigned int flags = SQ_OPEN_READ );

	void DisConnect();

	bool ExecuteSQL( const char* szSql );

	bool ExecuteSQL( const char* szSql, CEXSQLiteExecuteObject& execute );

	bool ExecuteQuerySQL( const char* szSql, CEXSQLiteQueryObject& pquery );

	struct sqlite3_stmt* ComplieSQL( const char* szSql );

public:

	bool IsConnected() const
	{
		return NULL != m_pSqlite;
	}

	const std::string& GetDBName() const
	{
		return m_dbName;
	}

public:

	bool BeginTransactions( unsigned int model = TRANSACTION_DEFERRED );

	bool CommitTransactions();

	bool SetWALMode();

private:
	CEXSqlite( const CEXSqlite& );
	CEXSqlite& operator = ( const CEXSqlite& );

	bool							m_bCommitTransaction;
	struct sqlite3*					m_pSqlite;
	std::string						m_dbName;		// ascii
};

