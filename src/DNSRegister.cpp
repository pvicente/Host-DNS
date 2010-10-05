#include "DNSRegister.hpp"
#include <string.h>

namespace dns
{
	DNSRegister::DNSRegister(const utils::String &p_Name):HashNode(p_Name), m_ips(NULL), m_length()
	{

	}

	DNSRegister::DNSRegister(const utils::String &p_Name, uint32_t p_Ip):HashNode(p_Name), m_ips(new uint32_t[1]), m_length(1)
	{
		*m_ips = p_Ip;
	}


	DNSRegister::~DNSRegister()
	{
		delete [] m_ips;
	}

	bool DNSRegister::operator==(const DNSRegister &c) const
	{
		return GetName() == c.GetName();
	}

	bool DNSRegister::operator==(const utils::String &p_Name) const
	{
		return GetName() == p_Name;
	}

	bool DNSRegister::AppendIp(uint32_t p_Ip)
	{
		std::size_t i = 0;
		for(; i < m_length; i++)
		{
			if (m_ips[i] == p_Ip)
				break;	
		}

		if (  m_length == i )
		{
			uint32_t *temp = new uint32_t[m_length + 1];
			memcpy(temp, m_ips, m_length*sizeof(uint32_t));
			delete [] m_ips;

			m_ips = temp;
			m_ips[m_length++]=p_Ip;

			return true;
		}
		
		return false;
	}

	const utils::String& DNSRegister::GetName() const
	{
		return GetKey();
	}

	uint32_t DNSRegister::GetIP(std::size_t i)
	{
		return (m_ips)? m_ips[i]: 0;
	}

	std::size_t DNSRegister::length()
	{
		return m_length;
	}
}

