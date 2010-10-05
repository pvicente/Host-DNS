#ifndef DNSRESPONSE_HPP
#define DNSRESPONSE_HPP

#include "NonCopyable.hpp"
#include "DNSHeader.hpp"
#include "DNSRegister.hpp"
#include "DNSError.hpp"

namespace dns
{
/**
* @brief Implementes methods to generate correct DNS responses
*/
	class DNSResponse:public NonCopyable
	{
		private:
		DNSResponse();

		DNSHeader *m_header;
		std::size_t m_size;

/**
* @brief Initialize header of response with correct values
*
* @param response
*/
		void GenerateResponse(DNSHeader *response);

		public:

		explicit DNSResponse(char *request, std::size_t size);

/**
* @brief Generate a dns response with values in reg and store results in buf with size buflen
*
* @param reg DNSRegister founded or NULL if not
* @param buf Buffer to store response
* @param buflen
*
* @return size of DNS Response
*/
		std::size_t GenerateResponse(DNSRegister *reg, char *buf, std::size_t buflen);

/**
* @brief Generate a dns response with error traduced to DNS Response Code
*
* @param error
* @param buf
* @param buflen
*
* @return size of response
*/
		std::size_t GenerateResponse(eDNSError error, char *buf, std::size_t buflen);
	};
}


#endif


