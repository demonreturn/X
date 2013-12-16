#pragma once

#include "EXTypeDefine.h"
#include "EXStringConvert/EXStringConvert.h"

class CEXStringBuffer
{
public:
	CEXStringBuffer( UINT32 size = 4096 );
	~CEXStringBuffer();

	inline void AddString( const EXString& str );
	inline void AddString(const char* str);

	void AddString(const char* str, UINT32 len);	

	inline CEXStringBuffer& operator += (const EXString& str);
	inline CEXStringBuffer& operator += (const char* str);

	inline const char* GetString() const;
	inline UINT32 GetLength() const;

	inline void Clear();

private:
	CEXStringBuffer(const CEXStringBuffer&);
	CEXStringBuffer& operator = (const CEXStringBuffer&);

	UINT32							m_size;
	std::vector<char>				m_buffer;
};

// inline function:

inline void CEXStringBuffer::AddString( const EXString& str )
{
	AddString(str.c_str(), str.length());
}

inline void CEXStringBuffer::AddString( const char* str )
{
	AddString(str, strlen(str));
}

inline CEXStringBuffer& CEXStringBuffer::operator+=( const EXString& str )
{
	AddString(str);

	return *this;
}

inline CEXStringBuffer& CEXStringBuffer::operator+=( const char* str )
{
	AddString(str);

	return *this;
}

inline const char* CEXStringBuffer::GetString() const
{
	return &m_buffer[0];
}

inline UINT32 CEXStringBuffer::GetLength() const
{
	return m_size;
}

inline void CEXStringBuffer::Clear()
{
	memset(&m_buffer[0], 0, m_size);
	m_size = 0;
}


//////////////////////////////////////////////////////////////////////////

class CVxOStringStream
{
public:
	CVxOStringStream(CEXStringBuffer* buff = NULL)
		: m_strBuffer(buff)
		, m_bAutoDelete(false)
	{
		if (m_strBuffer == NULL)
		{
			m_strBuffer = new CEXStringBuffer();
			m_bAutoDelete = true;
		}
	}

	~CVxOStringStream()	
	{
		if (m_bAutoDelete)
		{
			delete m_strBuffer;
			m_strBuffer = NULL;
		}
	}

	inline const char* GetString() const
	{
		return m_strBuffer->GetString();
	}

	inline UINT32 GetLength() const
	{
		return m_strBuffer->GetLength();
	}

	inline void Clear()
	{
		m_strBuffer->Clear();
	}

	inline CVxOStringStream& operator << (INT8 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (UINT8 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (INT16 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (UINT16 val){ write(val);	return *this; }
	inline CVxOStringStream& operator << (INT32 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (UINT32 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (INT64 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (UINT64 val){ write(val); return *this; }
	inline CVxOStringStream& operator << (FLOAT val){ write(val); return *this; }
	inline CVxOStringStream& operator << (DOUBLE val){ write(val); return *this; }
	inline CVxOStringStream& operator << (const std::string& val)
	{ 
		*m_strBuffer += val;

		return *this; 
	}

private:
	template<class T>
	inline void write(const T& val)
	{
		std::string str;
		EX_STRING::ToString(str, val);

		*m_strBuffer += str;
	}

private:
	CEXStringBuffer*					m_strBuffer;
	bool								m_bAutoDelete;
};