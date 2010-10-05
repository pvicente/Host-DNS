#include "LogSystem.hpp"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>

namespace utils
{
	static const char *progname = PROGRAM_NAME;
	static const int max_line_length = 1024;

	Log::Log()
	{
		openlog(progname,LOG_CONS|LOG_PID,LOG_DAEMON|LOG_INFO);			
	}

	Log::~Log()
	{
		closelog();
	}


	void Log::Write(const char *format, ...)
	{
		va_list parg;
		va_start(parg, format);

		char msg[max_line_length];
		vsnprintf(msg, sizeof(msg), format, parg );			

		syslog(LOG_INFO, "%s", msg);

		va_end(parg);
	
	}


	void Log::WriteErr(const char *format, ...)
	{
		va_list parg;
		va_start(parg, format);

		char msg[max_line_length];
		vsnprintf(msg, sizeof(msg), format, parg );			

		fprintf(stderr, "%s", msg);
		Write("%s", msg);

		va_end(parg);
	}
}
