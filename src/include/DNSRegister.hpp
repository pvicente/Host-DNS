#ifndef DNS_REGISTER_HPP
#define DNS_REGISTER_HPP

#include <stdint.h>
#include "NonCopyable.hpp"
#include "HashTable.hpp"
#include "String.hpp"

namespace dns
/**
* @brief Store ips from name
*/
{
	class DNSRegister:public NonCopyable, public utils::HashNode
	{
		private:
		DNSRegister();

		uint32_t *m_ips;
		std::size_t m_length;

		public:
		DNSRegister(const utils::String &p_Name);
		DNSRegister(const utils::String &p_Name, uint32_t p_Ip);

		~DNSRegister();
		
		bool operator==(const DNSRegister &c) const;
		bool operator==(const utils::String &p_Name) const;

/**
* @brief Append p_Ip to list if not exists
*
* @param p_Ip IPV4 for append
*
* @return successfull status
*/
		bool AppendIp(uint32_t p_Ip);

		const utils::String& GetName() const;
		
/**
* @brief Return IP with index i
*
* @param i Index
*
* @return 
*/
		uint32_t GetIP(std::size_t i);
		

/**
* @brief Return size of IP List
*
* @return 
*/
		std::size_t length();
	
	};
}

#endif

