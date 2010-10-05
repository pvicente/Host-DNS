#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>

namespace utils
{
/**
* @brief Implements String class with similar interface with std
*/
	class String
	{
		private:
		char *m_buf;
		std::size_t m_length;
		std::size_t m_size;	

		static void Swap(String &a, String &b);
	
		public:

		String();
		String(const String &p_str);
		String(const char *p_str);
		String(std::size_t p_length);
		
		~String();
		
		String& operator=(const String &p_str);

		bool operator==(const String &p_str) const;
		bool operator!=(const String &p_str) const;
		bool operator<(const String &p_str) const;
		
		String operator+(const String &p_str);
		String operator+(const char *p_str);

		char& operator[](std::size_t p_pos);
		char& operator[](std::size_t p_pos) const;

		const char * c_str() const;
		std::size_t length() const;
		std::size_t size() const;

/**
* @brief Append char to string. String do not grow if is needed
*
* @param c
*
* @return true if successful
*/
		bool append(char c);

		void clear();
		
/**
* @brief Return the last char of string
*
* @return 
*/
		char back() const;
	};
}

#endif

