#include "DNSRequest.hpp"
#include "Utils.hpp"

namespace dns
{
	DNSRequest::DNSRequest(char *request, std::size_t size):m_request(reinterpret_cast<DNSHeader *>(request)), m_size(size)
	{
		
	}
	
	eDNSError DNSRequest::Parse(DNSQuery &query)
	{
		if (!m_request->IsQuestion())
			return ERR_RESPONSE_BIT_SET;

		if (!m_request->IsStandardQuery())
			return ERR_NOT_IMPLEMENTED;

		if (m_size < sizeof(DNSHeader))
			return ERR_MALFORMED_REQUEST;

		if (m_request->IsTruncated())
			return ERR_QUESTION_TRUNCATED;

		uint16_t n_questions = m_request->GetQuestions();
		if (n_questions == 0)
			return ERR_NO_QUESTION;
		
		if (n_questions > 1)
			return ERR_MULTI_QUESTIONS;
		
		char *end = reinterpret_cast<char *>(m_request) + m_size;
		char *query_section = reinterpret_cast<char *>(m_request) + sizeof(DNSHeader);
		if (query_section >= end)
			return ERR_NO_QUESTION;

		eDNSError error = query.Parse(query_section, end - query_section);

		if ( error == ERR_NONE)
		{
			if (query.IsSupported())
			{
				utils::String enc_name(query.GetName());
				error = utils::DnsEncode(enc_name);
			}
			else
			{
				error = ERR_NOT_IMPLEMENTED;
			}
		}

		return error;
	}

}

