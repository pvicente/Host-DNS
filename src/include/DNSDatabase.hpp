#ifndef DNS_DATABASE_HPP
#define DNS_DATABASE_HPP

#include <map>
#include <strings.h>
#include "DNSRegister.hpp"
#include "NonCopyable.hpp"
#include "String.hpp"
#include "HashTable.hpp"

namespace dns
{

/**
* @brief Class to store DNSRegisters and to Find names
*/
	class DNSDatabase:public NonCopyable
	{
		private:

		utils::HashTable m_db;

		public:
		DNSDatabase();
		~DNSDatabase();

/**
* @brief Find name in data structure
*
* @param p_Name Name to be find
*
* @return Ptr to DNSRegister or NULL if search has not been successful
*/
		DNSRegister* Find(const utils::String &p_Name);


/**
* @brief Load Data from p_Filename, with file format like /etc/hosts
*
* @param p_FileName Path to file
*/
		void Load(const char *p_FileName);	
	};
}

#endif

