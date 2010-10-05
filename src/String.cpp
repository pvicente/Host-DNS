#include "String.hpp"
#include <string.h>
#include <stdlib.h>

namespace utils
{
	void String::Swap(String &a, String &b)
	{
		char *temp_buf;
		std::size_t temp_size;
		std::size_t temp_length;
		
		temp_buf = a.m_buf;
		a.m_buf = b.m_buf;
		b.m_buf = temp_buf;

		temp_size = a.m_size;
		a.m_size = b.m_size;
		b.m_size = temp_size;

		temp_length = a.m_length;
		a.m_length = b.m_length;
		b.m_length =temp_length; 
	}


	String::String():m_buf(new char[1]), m_length(0), m_size(1)
	{
		m_buf[0]='\0';
	}

	String::String(const String &p_str):m_buf(new char[p_str.length() + 1]), m_length(p_str.length()), m_size(m_length + 1)
	{
		memcpy(m_buf, p_str.m_buf, m_size);
	}
 
	String::String(const char *p_str):m_buf(new char[ ((p_str == NULL)? 0: strlen(p_str)) + 1]), m_length( (p_str == NULL)? 0: strlen(p_str) ), m_size(m_length + 1)
	{
		if (p_str)
		{
			memcpy(m_buf, p_str, m_size);
		}
		else
		{
			m_buf[0]='\0';
		}
	}

	String::String(std::size_t p_length):m_buf(new char[p_length + 1]), m_length(0), m_size(p_length + 1)
	{
		m_buf[0]='\0';
	}

	String::~String()
	{
		delete [] m_buf;
	}

	String& String::operator=(const String &p_str)
	{
		if (m_size > p_str.length())
		{
			memcpy(m_buf, p_str.m_buf, p_str.length() + 1);
			m_length = p_str.length();
		}
		else
		{
			String temp_str(p_str);
			Swap(*this, temp_str);
		}
		
		return *this;	
	}

	bool String::operator==(const String &p_str) const
	{
		return strcmp(m_buf, p_str.m_buf) == 0; 
	}

	bool String::operator!=(const String &p_str) const
	{
		return !(*this == p_str);
	}

	bool String::operator<(const String &p_str) const
	{
		return strcmp(m_buf, p_str.m_buf) < 0;
	}

	String String::operator+(const String &p_str)
	{
		String res(m_length + p_str.length());

		res.m_buf = strcpy(res.m_buf, m_buf);
		res.m_buf = strcat(res.m_buf, p_str.m_buf);
		res.m_length = strlen(res.m_buf);

		if ( res.m_length != m_length + p_str.length())
			abort();

		return res;
	}

	String String::operator+(const char *p_str)
	{
		return (*this + String(p_str));
	}

	char& String::operator[](std::size_t p_pos)
	{
		return m_buf[p_pos];
	}

	char& String::operator[](std::size_t p_pos) const
	{
		String& res = const_cast<String&>(*this);
		return res[p_pos];
	}

	const char * String::c_str() const
	{
		return m_buf;
	}

	std::size_t String::length() const
	{
		return m_length;
	}

	std::size_t String::size() const
	{
		return m_size;
	}

	bool String::append(char c)
	{
		if (m_length + 1 < m_size)
		{
			m_buf[m_length++] = c;
			m_buf[m_length] = '\0';
			return true;
		}
		return false;
	}

	void String::clear()
	{
		m_buf[0] = '\0';
		m_length = 0;
	}

	char String::back() const
	{
		return m_buf[m_length-1];
	}
}

