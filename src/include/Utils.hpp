#ifndef UTILS_HPP
#define UTILS_HPP

#include "StringList.hpp"
#include "DNSError.hpp"
#include <stdint.h>

namespace utils
{
/**
* @brief Convert network IP (p_src) to printable format
*
* @param p_family (AF_INET, AF_INET6)
* @param p_src 
* @param p_dest
*
* @return successfull or not
*/
	bool Inet_ntop(int p_family, void *p_src, String &p_dest);


/**
* @brief Convert source IP( in string format) to network format
*
* @param p_family (AF_INET, AF_INET6)
* @param p_src
* @param p_dest
*
* @return successfull or not
*/
	bool Inet_pton(int p_family, const char *p_src, void *p_dest);

/**
* @brief Generate StringList of interfaces up and configured in the system
*
* @param l
*/
	void GetInterfaceList(StringList &l);

/**
* @brief Decode a DNS name without support of compression methods, used to compress size of dns messages 
*
* @param start
* @param slen
* @param name Store DNS decoded name here
* @param error modify error 
*
* @return End of name
*/
	char* DnsDecode(char *start, std::size_t slen, String& name, dns::eDNSError &error);

/**
* @brief Encode DNS name in Str, with valid format in DNS Queries and Responses
*
* @param str
*
* @return ERR_NONE if successful or other if not
*/
	dns::eDNSError DnsEncode(String &str);

/**
* @brief print a buffer with hexvalues
*
* @param buf
* @param len
*/
	void VuelcaBuffer(const void *buf, int len);

/**
* @brief Write uint16_t in src with correct endianess
*
* @param src
* @param value
*
* @return 
*/
	char* Put16(char *src, uint16_t value);

/**
* @brief Write uint32_t in src with correct endianess
*
* @param src
* @param value
*
* @return 
*/
	char* Put32(char *src, uint32_t value);
}


#endif

