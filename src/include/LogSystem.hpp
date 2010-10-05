#ifndef LOG_SYSTEM_HPP
#define LOG_SYSTEM_HPP

#include "NonCopyable.hpp"

namespace utils
{
/**
* @brief Implements Log System Manager.
*/
	class Log:public NonCopyable
	{
		public:
		Log();
		~Log();

		static Log& Instance()
		{
			static Log l;
			return l;
		}

/**
* @brief Write to syslog data with varg list of parameters
*
* @param format
* @param ...
*/
		void Write(const char *format, ...);


/**
* @brief Write to stderr and syslog data with varg list of parameters
*
* @param format
* @param ...
*/
		void WriteErr(const char *format, ...);
	};
}


#endif

