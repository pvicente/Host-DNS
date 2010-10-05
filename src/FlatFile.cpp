#include "FlatFile.hpp"
#include "Tokenizer.hpp"
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


namespace utils
{

	static 	bool isRegularFile(const char *file_name)
	{
		struct stat buffer;
		lstat(file_name, &buffer);
		bool res = S_ISREG(buffer.st_mode);
		return res;
	}

	FlatFile::FlatFile(const char *p_src):m_FileName(p_src), m_File(NULL), m_Line(0)
	{
		if (isRegularFile(m_FileName.c_str()))
			m_File = fopen(m_FileName.c_str(), "rt");
	}

	FlatFile::~FlatFile()
	{
		if (m_File)
			fclose(m_File);
	}

	String FlatFile::GetLine()
	{
		static const std::size_t max_line = 1024;
		String retvalue;

		if (!m_File)
			return retvalue;

		char buf[max_line];
		while (fgets(buf, sizeof(buf), m_File) != NULL) 
		{
			m_Line++;
    			buf[strcspn(buf, "\n")] = '\0';
    			if (buf[0] == '\0')
        			break;
		
			retvalue = retvalue + String(buf);	
			if (strlen(buf) != sizeof(buf) -1)
				break;	
		}

		return retvalue;
	}

	std::size_t FlatFile::GetNumberOfLine() const
	{
		return m_Line;
	}

	const char* FlatFile::GetFilename() const
	{
		return m_FileName.c_str();
	}

	bool FlatFile::eof() const
	{
		return !m_File || feof(m_File);
	}

	FlatFile::operator bool() const
	{
		return m_File != NULL;
	}

	int FlatFile::error() const
	{
		return ferror(m_File);
	}
}

