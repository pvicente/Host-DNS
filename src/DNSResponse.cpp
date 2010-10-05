#include "DNSResponse.hpp"
#include "DNSDefine.hpp"
#include "Utils.hpp"
#include <string.h>

namespace dns
{
	static eRESP error_to_responsecode(eDNSError error)
	{
		eRESP res = RREFUSED;

		switch(error)
		{
			case ERR_Q_BUFFER_OVERFLOW:
			case ERR_Q_INVALID_COMPRESSION:
			case ERR_Q_NAME_TOO_LONG:
			case ERR_LABEL_TOO_LONG:
			case ERR_NAME_FORMAT:
			case ERR_INVALID_TYPE:
			case ERR_INVALID_CLASS:
			case ERR_QUESTION_TRUNCATED:
			case ERR_MALFORMED_REQUEST:
			case ERR_RESPONSE_BIT_SET:
							res = RQUERY_FORMAT;
			break;

			case ERR_NO_QUESTION:
			case ERR_MULTI_QUESTIONS:
			case ERR_UNSUPPORTED_TYPE:
			case ERR_UNSUPPORTED_CLASS:
			case ERR_NOT_IMPLEMENTED:
							res = RNOT_IMPLEMENTED;
			break;

			default:
				res = RREFUSED;

		};
		return res;
	}


	DNSResponse::DNSResponse(char *request, std::size_t size):m_header(reinterpret_cast<DNSHeader *>(request)), m_size(size)
	{
		
	}
	
	void DNSResponse::GenerateResponse(DNSHeader *response)
	{
		response->SetResponse();
		response->SetRecursion(false);
		response->SetRecursionDesired(false);
		response->SetAuthoritative(false);
		response->SetStandardQuery();
		response->SetAnswers(0);
		response->SetResponseCode(RNO_ERROR);
	}
	
	std::size_t DNSResponse::GenerateResponse(DNSRegister *reg, char *buf, std::size_t buflen)
	{
		memcpy(buf, m_header, m_size); //Copy original request to add response

		DNSHeader *response_header = reinterpret_cast<DNSHeader *>(buf);
		GenerateResponse(response_header);

		std::size_t response_size = m_size;
		std::size_t response_max_size = buflen;

		if (reg == NULL)
		{
			response_header->SetResponseCode(RNOT_FOUND);
			return response_size;
		}
		
		std::size_t i = 0;
		bool truncated = (response_size + 16 > response_max_size);
		char *answer = reinterpret_cast<char *>(response_header) + response_size;

		for( i = 0; i < reg->length() && !truncated; i++, response_size+=16, truncated = (response_size + 16 > response_max_size) )
		{
			static uint16_t name_offset=sizeof(DNSHeader) | 0xC000;
			static uint32_t ttl = 300;

			using namespace utils;
			//PutName compressed
			answer = Put16(answer, name_offset);
			answer = Put16(answer, dns::TA);
			answer = Put16(answer, dns::CIN);
			answer = Put32(answer, ttl);
			answer = Put16(answer, sizeof(uint32_t));
			answer = Put32(answer, reg->GetIP(i));
		}

		response_header->SetAnswers(i);
		response_header->SetTruncated(truncated);

		return response_size;
	}

	std::size_t DNSResponse::GenerateResponse(eDNSError error, char *buf, std::size_t buflen)
	{
		memcpy(buf, m_header, m_size); //Copy original request to add response

		DNSHeader *response_header = reinterpret_cast<DNSHeader *>(buf);
		GenerateResponse(response_header);
		std::size_t response_size = m_size;

		response_header->SetResponseCode(error_to_responsecode(error));
		return response_size;
	}
	
}

