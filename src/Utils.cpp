#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <cstdio>
#include <new>
#include <cstring>
#include <unistd.h>
#include <ctype.h>

#include "Utils.hpp"
#include "DNSError.hpp"
#include "DNSDefine.hpp"

#include "LogSystem.hpp"


namespace utils
{
	void VuelcaBuffer(const void *buf, int len)
	{
		int i, j;
		const int WIDE = 16;
		unsigned char *ptr_buf = (unsigned char *)buf;

		for (i = 0 ; i < len ; i += WIDE)
		{
			for (j = i ; j < i + WIDE ; j++) {
				if (j < len) {
					printf("%02X ", ptr_buf[j]);
				} else {
					printf("   ");
				}

				if (j == i + (WIDE / 2) - 1) {
					printf(" ");
				}
			}

			printf("| ");

			for (j = i ; j < i + WIDE ; j++) {
				if (j < len) {
					if (isprint(ptr_buf[j]))
						printf("%c", ptr_buf[j]);
					else
						printf(".");
				} else {
					printf(" ");
				}
			}

			printf("\n");
		}
	}

	bool Inet_ntop(int p_family, void *p_src, String &p_dest)
	{
		char str[INET6_ADDRSTRLEN];
	
		switch (p_family)
		{
			case AF_INET:
			case AF_INET6:
				if(inet_ntop(p_family, p_src, str, sizeof str) != NULL)
				{
					p_dest = String(str);
					return true;
				}
				break;
		};

		return false;
	}

	bool Inet_pton(int p_family, const char *p_src, void *p_dest)
	{
		int res = 0;

		switch(p_family)
		{
			case AF_INET:
			case AF_INET6:
				res = inet_pton(p_family, p_src, p_dest);			
				break;
		};

		return res == 1;
	}

	void GetInterfaceList(StringList &list)
	{
		int sockfd;

		if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			utils::Log::Instance().Write("get_ifconfig: error creating socket for interface scan");
			return;
		}

		struct ifconf ifc;

		std::size_t buflen = 8192;
		char *buf = NULL;

		for (;;)
		{
			try
			{
				buf = new char[buflen];
				int n = 0;

				ifc.ifc_len = buflen;
				ifc.ifc_buf = buf;

				if ((n = ioctl(sockfd, SIOCGIFCONF, (char *)&ifc)) != -1)
				{
					if (ifc.ifc_len + 2 * sizeof(struct ifreq) < buflen)
						break;
				}
				if ((n == -1) && errno != EINVAL)
				{
					utils::Log::Instance().Write("get_ifconfig: error setting SIOCGIFCONF for interface scan");
					delete [] buf;
					close(sockfd);
					return;
				}
				
				delete [] buf;
				buflen += 4096;
			}
			catch( std::bad_alloc )
			{
				close(sockfd);
				return;
			}
		}

		struct ifreq *ifr;

		for (int n = 0; n < ifc.ifc_len;)
		/* Scan interfaces */
		{
			struct in_addr addr4;

			ifr = (struct ifreq *)((char *)ifc.ifc_req + n);

#ifdef HAVE_SOCKADDR_SA_LEN
			n += sizeof(ifr->ifr_name) + (ifr->ifr_addr.sa_len > sizeof(struct sockaddr) ? ifr->ifr_addr.sa_len : sizeof(struct sockaddr));
#else
			n += sizeof(struct ifreq);
#endif /* HAVE_SOCKADDR_SA_LEN */

			if (ifr->ifr_flags & IFF_UP) /* Must be up */
				continue;
			if (ioctl(sockfd, SIOCGIFADDR, ifr) < 0)/* Get address */
				continue;

			switch (ifr->ifr_addr.sa_family)
			{
				case AF_INET:
					memcpy(&addr4, &((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr, sizeof(struct in_addr));

					String temp;
					if (Inet_ntop(AF_INET, &addr4, temp) && list.find(temp) == list.end())
					{
						list.push_back(temp);
					}
					break;
			}
		}

		delete []buf;
		close(sockfd);
	}

	char* DnsDecode(char *start, std::size_t slen, String& name, dns::eDNSError &error)
	{
		using namespace dns;
		char *end=start+slen;
		
		register char   *s = start,   /* Current pointer into input */
				n, len;

		error = ERR_NONE;

		if (*s == 0)  /* The name is just "." */
		{
			name=".";
			return (s+1);
		}

		String dest(dns::DNS_Max_Name_Len);

		while ((len = *s))  /* Get length octet */
		{
			register unsigned char mask = len & 0xC0;

			if (mask == 0xC0 || mask == 0x40 || mask == 0x80)
			{
				error = ERR_Q_INVALID_COMPRESSION;
				return (NULL);
			}
			else
			{
				s++;
				if (s+len > end)
				{
					error = ERR_Q_BUFFER_OVERFLOW;
					return NULL;
				}
				for (n = 0; n < len; n++)    /* Get label */
				{
					if (!dest.append(tolower(*s++)))
					{
						error = ERR_Q_NAME_TOO_LONG;
						return NULL;
					}
				}
				
				if (!dest.append('.'))
				{
					error = ERR_Q_NAME_TOO_LONG;
					return NULL;
				}
			}
		}

		name = dest;
		return s+1;
	}

	dns::eDNSError DnsEncode(String &str)
	{
		using namespace dns;

		if (str.back() != '.')
		{
			return ERR_NAME_FORMAT;
		}

		String temp = String(".") + str;
		std::size_t last_dot=0;

		for (std::size_t i = 0; i <str.length();i++)
		{
			if(str[i] == '.')
			{
				std::size_t len = i - last_dot;
				if (len > 63)
				{
					return ERR_LABEL_TOO_LONG;
				}
				temp[last_dot==0?last_dot:last_dot+1] = (char)(len);
				last_dot = i;
			}
		}

		temp[temp.length() - 1] = '\0';

		str = String(temp.c_str());
		return ERR_NONE;
	}

	char* Put16(char *src, uint16_t value)
	{
		*reinterpret_cast<uint16_t*>(src) = htons(value);
		return src + sizeof(uint16_t);
	}

	char* Put32(char *src, uint32_t value)
	{
		*reinterpret_cast<uint32_t*>(src) = htonl(value);
		return src + sizeof(uint32_t);
	}
}

