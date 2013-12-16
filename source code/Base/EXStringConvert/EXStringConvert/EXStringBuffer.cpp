
#include "EXStringBuffer.h"
#include <assert.h>

CEXStringBuffer::CEXStringBuffer( UINT32 size /*= 4096 */ )
	: m_size(0)
{
	m_buffer.resize(size, 0);
}


CEXStringBuffer::~CEXStringBuffer(void)
{
}

void CEXStringBuffer::AddString( const char* str, UINT32 len )
{
	assert(str != NULL);
	if (len == 0)
	{
		return;
	}

	if ((len + m_size) >= m_buffer.size())
	{
		m_buffer.resize(2*m_buffer.size());
	}

	memcpy(&m_buffer[m_size], str, len);
	m_size += len;
}
