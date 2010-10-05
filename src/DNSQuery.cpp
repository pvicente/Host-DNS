#include <arpa/inet.h>
#include "DNSQuery.hpp"
#include "Utils.hpp"

namespace dns
{
	DNSQuery::DNSQuery(): m_name(DNS_Max_Name_Len), m_type(0), m_class()
	{
	}

	const utils::String& DNSQuery::GetName() const
	{
		return m_name;
	}

	eTYPE DNSQuery::GetType() const
	{
		return (eTYPE) m_type;
	}

	eCLASS DNSQuery::GetClass() const
	{
		return (eCLASS) m_class;
	}

	bool DNSQuery::IsSupported() const
	{
		return (m_class == CIN || m_class == CANY) && (m_type == TA || m_type == TANY); 
	}

	void DNSQuery::clear()
	{
		m_name.clear();
		m_type = 0;
		m_class = 0;
	}

	eDNSError DNSQuery::Parse(char *qsection, std::size_t size)
	{
		eDNSError error;
		char *end = qsection + size;

		char *current = utils::DnsDecode(qsection, size, m_name, error);

		if (error != ERR_NONE)
			return error;

		if (current >= end)
		{
			return ERR_QUESTION_TRUNCATED;
		}

		m_type = ntohs(*reinterpret_cast<uint16_t*>(current));

		if (m_type > 16 && (m_type < 252 || m_type > 255))
		{
			return ERR_INVALID_TYPE;
		} 

		current = current + 2;

		if (current >= end)
		{
			return ERR_QUESTION_TRUNCATED;
		}

		m_class = ntohs(*reinterpret_cast<uint16_t*>(current));

		if (m_class > 4 && m_class != 255)
		{
			return ERR_INVALID_CLASS;
		}
		
		return ERR_NONE;
	}	
}
