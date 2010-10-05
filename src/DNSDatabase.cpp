#include "DNSDatabase.hpp"
#include "FlatFile.hpp"
#include "Tokenizer.hpp"
#include "Utils.hpp"
#include "LogSystem.hpp"
#include <arpa/inet.h>

namespace dns
{
	DNSDatabase::DNSDatabase():m_db(1024)
	{
	}

	DNSDatabase::~DNSDatabase()
	{

	}

	DNSRegister* DNSDatabase::Find(const utils::String &p_Name)
	{
		return static_cast<DNSRegister*>(m_db.find(p_Name));
	}	

	void DNSDatabase::Load(const char *p_FileName)
	{
		using namespace utils;

		FlatFile file(p_FileName);
		
		if (!file)
		{
			Log::Instance().WriteErr("Error opening: Host file %s\n", p_FileName);
			return;
		}

		while(!file.eof())
		{
			String line(file.GetLine());

			if (line == "")
			{
				continue;
			}

			Tokenizer t(line.c_str()," \t");
			if (t.length() <= 1)
			{
				Log::Instance().Write("%s:Line %d. Line does not have valid data to insert in Database\n", p_FileName, file.GetNumberOfLine());
				continue;
			}
		
			uint32_t ip = 0;
			if ( ! Inet_pton(AF_INET, t[0], &ip) )
			{
				Log::Instance().Write("%s:Line %d. Cannot convert %s to IPV4 address\n", p_FileName, file.GetNumberOfLine(), t[0]);
			}
			else
			{
				ip = ntohl(ip);
				for (uint32_t i = 1; i < t.length(); i++)
				{
					String name(t[i]);

					if (name.back() != '.')
						name = name + ".";

					String decoded_name(name);
					if ( DnsEncode(decoded_name) != ERR_NONE )
					{
						Log::Instance().Write("%s:Line %d. %s is not a valid dns name\n", p_FileName, file.GetNumberOfLine(), t[i]);
						continue;
					}

					DNSRegister *f = Find(name);

					if (!f)
					{
						DNSRegister *temp = new DNSRegister(name, ip);
						if(!m_db.insert(temp))
						{
							delete temp;
							Log::Instance().Write("%s:Line %d. Abnormal error inserting register name:%s ip:%s\n"
									" in Database\n", p_FileName, file.GetNumberOfLine(), t[i], t[0]);
						}
					}
					else
					{
						if (!f->AppendIp(ip))
						{
							Log::Instance().Write("%s:Line %d. Ip %s Already exists in Database asociated with name %s\n",
									p_FileName, file.GetNumberOfLine(), t[0], t[i]);
						}
					}
				}
			}
		}
	}
}


