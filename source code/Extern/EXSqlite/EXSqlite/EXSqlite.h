// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EXSQLITE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EXSQLITE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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

// �����Ǵ� EXSqlite.dll ������
class EXSQLITE_API CEXSqlite 
{
public:
	enum FLAG
	{
		SQ_OPEN_READ = 0x01,
		SQ_OPEN_WRITE= 0x01 << 1
	};

	/*
	 * ����ģʽ��
	 * TRANSACTION_DEFERRED		������ʱ�������������ݿ⣬��һ�γ����޸����ݿ����ʱ����������ݿ⣬��ʱֻ��һ��д����
	 *							 �����ж��������
	 * TRANSACTION_DEFERRED		�������ɹ�ʱ���������ݿ⣬����֤û������д���ݿ����ӣ�ֻ��һ��д���ӡ��������ж��������
	 * TRANSACTION_EXCLUSIVE	�������ɹ�ʱ����ֻ֤��һ�����ӣ���û���������ӡ�
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

