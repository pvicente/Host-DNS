#ifndef DNS_SERVER_HPP
#define DNS_SERVER_HPP

#include "NonCopyable.hpp"
#include "DNSDatabase.hpp"
#include <stdint.h>

namespace dns
{
/**
* @brief Instance of DNSServer
*/
	class DNSServer:public NonCopyable
	{
		private:
		DNSServer();

/**
* @brief Make all work of dns process 
*
* @param udp_fd file descriptor of sockets to make select
* @param n_fd number of descriptor
*/
		void Work(int *udp_fd, int n_fd);

/**
* @brief ReadRequest from file descriptor
*
* @param fd
*/
		void ReadRequest(int fd);

/**
* @brief Process a request and generate a correct dns response 
*
* @param in request
* @param len_in requestlen
* @param out output
* @param len_out outputsize
*
* @return size of response
*/
		int ProcessRequest(char *in, int len_in, char *out, int len_out);

		private:
		DNSDatabase m_db;
		uint16_t m_port;
		
		public:
		explicit DNSServer(const char *db_filename, uint16_t port);
		~DNSServer();

		bool Run();
	};
}

#endif

