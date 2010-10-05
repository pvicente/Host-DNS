#ifndef DNS_QUERY_HPP
#define DNS_QUERY_HPP

#include "String.hpp"
#include "DNSError.hpp"
#include "NonCopyable.hpp"
#include "DNSDefine.hpp"
#include <stdint.h>

namespace dns
{
/**
* @brief Encapsulate DNS Standard Query
*/
	class DNSQuery:public NonCopyable
	{
		private:
		utils::String m_name;
		uint16_t m_type;
		uint16_t m_class;

		public:
		DNSQuery();

		const utils::String& GetName() const;
		eTYPE GetType() const;
		eCLASS GetClass() const;

/**
* @brief Check if type and class or request are supported
*
* @return 
*/
		bool IsSupported() const;

/**
* @brief Clear contents of Query
*/
		void clear();

/**
* @brief Parse question register and store value in members of this class
*
* @param qsection begin of question register
* @param m_size size of question register
*
* @return ERR_NONE if successful, other error if not. 
*/
		eDNSError Parse(char *qsection, std::size_t m_size);
	};
}

#endif

