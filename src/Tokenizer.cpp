#include "Tokenizer.hpp"
#include <cstring>
#include <cstdlib>

namespace utils
{
	Tokenizer::Tokenizer(const char *p_str, const char *p_strdelim): m_str(strdup(p_str)), m_tokens(NULL), m_values(0) 
	{
		parseTokens(p_strdelim);
	}

	Tokenizer::~Tokenizer()
	{
		free(m_str);
		free(m_tokens);
	}

	void Tokenizer::parseTokens(const char * p_strdelim)
	{
		char *str = m_str;

		std::size_t allocated = 0;
		std::size_t i = 0;

		char *save_ptr, *token;

		for(token = strtok_r(str, p_strdelim, &save_ptr); token; token = strtok_r(NULL, p_strdelim, &save_ptr), i++)
		{
			if ( i == allocated)
			{
				allocated += 10;
				m_tokens = static_cast<char **>(realloc(m_tokens, allocated * sizeof(char *)));
				if (!m_tokens)
					return;
			}

			m_tokens[i]=token;
		}

		m_values = i;
	}

	const char * Tokenizer::operator[] (std::size_t i)
	{
		if (m_tokens != NULL && i < m_values)
			return m_tokens[i];
		else
			return NULL;
	}

	std::size_t Tokenizer::length() const
	{
		return m_values;		
	}
}

