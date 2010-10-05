#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include "DNSServer.hpp"
#include "LogSystem.hpp"

int main( int argc, char **argv )
{
	utils::String hosts_file("/etc/hosts");
	static uint16_t port = 53;

	int opt = 0;

	while((opt = getopt(argc, argv, "p:h:")) != -1)
	{
		switch (opt)
		{
			case 'p':
				{
					int tmp_port = atoi(optarg);
					if (tmp_port < 1 || tmp_port > 65535)
					{
						printf("Error: Invalid port value %d. Value must be [1..65535]\n", tmp_port);
						exit(EXIT_FAILURE);
					}
					port = tmp_port;
				}
				break;
			case 'h':
				hosts_file = optarg;
				break;
			default:
				puts("Usage:");
				puts("\t-p\tUDP port number");
				puts("\t-h\tHosts file path");
				puts("");
				exit(EXIT_FAILURE);
				break;
		};
	}

	using namespace dns;

	int res = EXIT_SUCCESS;

	try
	{
		DNSServer service(hosts_file.c_str(), port);
		res = service.Run() ? EXIT_SUCCESS: EXIT_FAILURE;
	}
	catch (std::bad_alloc& ba )
	{
		utils::Log::Instance().Write("Error. Bad Alloc exception in program. %s\n", ba.what());
		res = EXIT_FAILURE;
	}

	exit(res);
}


