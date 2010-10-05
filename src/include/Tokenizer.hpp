#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "NonCopyable.hpp"
#include <cstddef>

namespace utils
{
	class Tokenizer:public NonCopyable
	{
		private:
		char * m_str;
		char ** m_tokens;
		std::size_t m_values;
		
		private:
/**
* @brief Method to parse string in a secuence of tokens
*
* @param p_strdelim set of characters that delimit the tokens in the parsed string
*/
		void parseTokens(const char *p_strdelim);

		public:
/**
* @brief Parse string in a secuence of tokens
*
* @param p_str string to be parsed
* @param p_strdelim set of characters that delimit the tokens in the parsed string
*/
		explicit Tokenizer(const char *p_str, const char *p_strdelim);

/**
* @brief Destructor
*/
		~Tokenizer();
	
/**
* @brief Operator[] to have an index access to Tokens
*
* @param i index,
*
* @return i-token of tokenized string or NULL of i is not valid
*/
		const char* operator[](std::size_t i);

/**
* @brief Number of tokens in tokenized string
*
* @return number >= 0
*/
		std::size_t length() const;
	};
}

#endif

