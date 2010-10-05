#ifndef DNSREQUEST_HPP
#define DNSREQUEST_HPP

#include "NonCopyable.hpp"
#include "DNSError.hpp"
#include "DNSQuery.hpp"
#include "DNSHeader.hpp"

namespace dns
{
/**
* @brief Parsed DNSRequest
*/
	class DNSRequest:public NonCopyable
	{
		private:
		DNSRequest();

		DNSHeader *m_request;
		std::size_t m_size;

		public:
		explicit DNSRequest(char *m_request, std::size_t size);
/**
* @brief Parse DNS Request and Store results in DNSQuery parameter
*
* @param c DNSQuery to store results
*
* @return ERR_NONE if successful, other error if not
*/
		eDNSError Parse(DNSQuery &c);
	};
}


#endif


