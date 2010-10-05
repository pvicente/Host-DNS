#ifndef FLAT_FILE_HPP
#define FLAT_FILE_HPP

#include "NonCopyable.hpp"
#include "String.hpp"
#include <cstdio>

namespace utils
{
/**
* @brief Implements FlatFile to read line by line
*/
	class FlatFile:public NonCopyable
	{
		private:
		String m_FileName;
		FILE *m_File;
		std::size_t m_Line;

		public:
		explicit FlatFile(const char *p_fileName);
		~FlatFile();		
	
/**
* @brief GetLine in file (with actual offset)
*
* @return String with line
*/
		String GetLine();

		std::size_t GetNumberOfLine() const;

		const char* GetFilename() const;

/**
* @brief End of File
*
* @return 
*/
		bool eof() const;

/**
* @brief Cast operator bool
*
* @return 
*/
		operator bool() const;

/**
* @brief Return error if exists
*
* @return 
*/
		int error() const;
	};
}


#endif

