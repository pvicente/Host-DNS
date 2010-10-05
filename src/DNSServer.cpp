#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include <alloca.h>

#include "DNSServer.hpp"
#include "Utils.hpp"
#include "StringList.hpp"

#include "DNSRequest.hpp"
#include "DNSQuery.hpp"
#include "DNSResponse.hpp"
#include "DNSDefine.hpp"

#include "LogSystem.hpp"

namespace dns
{
	static int ipv4_listen(utils::String &p_ip, uint16_t p_port)
	{
        	int fd;
		struct sockaddr_in sa;

		memset(&sa, 0, sizeof(struct sockaddr_in));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(p_port);
		utils::Inet_pton(AF_INET,  p_ip.c_str(), &sa.sin_addr);

	        if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		{
			utils::Log::Instance().WriteErr("DNSServer Error: creating udp socket\n");
			return -1;
		}
        
		//fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

        	if (bind(fd, reinterpret_cast<struct sockaddr *> (&sa), sizeof(struct sockaddr_in)) < 0)
		{
			utils::Log::Instance().WriteErr("DNSServer Error: binding (UDP) on: %s:%d. Check permission.\n", p_ip.c_str(), p_port);
			close(fd);
			return -1;
		}

		
                for (std::size_t n = 1; n < 1024; n++)
                {
                        std::size_t size = n * 1024;
                        if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size))) < 0)
                                break;
                }
        	
		return fd;
	}

	DNSServer::DNSServer(const char *db_filename, uint16_t port): m_db(), m_port(port)
	{
		m_db.Load(db_filename);
	}

	DNSServer::~DNSServer()
	{
	}
	
	bool DNSServer::Run()
	{
		using namespace utils;

		StringList listeningInterface;
		GetInterfaceList(listeningInterface);

		if (listeningInterface.size() == 0)
		{
			Log::Instance().WriteErr("DNSServer Error: There is not listening interface up\n");
			return false;
		}

		std::size_t n_udp = listeningInterface.size();
		int *udp_fd = static_cast<int*>(alloca(sizeof(int*) *n_udp));
		memset(udp_fd, -1, sizeof(udp_fd));
	
		std::size_t i = 0;
		bool any_descriptor_listening = false;

		for(StringList::iterator j = listeningInterface.begin(); j != listeningInterface.end(); j++, i++)
		{
			udp_fd[i] = ipv4_listen(*j, m_port);
			if (udp_fd[i] != -1)
				any_descriptor_listening = true;
		}
		
		if (!any_descriptor_listening)
			return false;

		Work(udp_fd, n_udp);

		for(std::size_t i = 0; i < n_udp; i++)
		{
			if (udp_fd[i] != -1)
				close(udp_fd[i]);
		}

		return true;
	}

	void DNSServer::Work(int *udp_fd, int n_fd)
	{
		int start_maxfd = -1;
		fd_set start_rfd;
		FD_ZERO(&start_rfd);

		for (int i = 0; i < n_fd; i++, start_maxfd = (udp_fd[i] > start_maxfd) ? udp_fd[i]: start_maxfd)
		{
			FD_SET(udp_fd[i], &start_rfd);
		}


		fd_set rfd;
		FD_ZERO(&rfd);
		int maxfd = 0;

		for(;;)
		{
			memcpy(&rfd, &start_rfd, sizeof(rfd));
			maxfd = start_maxfd;

			int rv = select(maxfd+1, &rfd, NULL, NULL, NULL); //No timeout
			if (rv < 0)
			{
				if (errno == EINVAL)
				{
					continue;
				}

				utils::Log::Instance().Write("Error in select %s\n", strerror(errno) );
				break;
			}

			if (rv > 0)
			{
				for (int i = 0; i < n_fd; i++)
				{
					if (FD_ISSET(udp_fd[i], &rfd))
					{
						ReadRequest(udp_fd[i]);
					}
				}
			}
		}
	}

	void DNSServer::ReadRequest(int fd)
	{
		struct sockaddr_in addr4;
		socklen_t addrlen = sizeof(addr4);
		char in[DNS_Max_Udp_Packet_Len];
		char out[DNS_Max_Udp_Packet_Len];

		memset(&in, 0, sizeof(in));
		int len = recvfrom(fd, &in, sizeof(in), 0, reinterpret_cast<struct sockaddr*>(&addr4), &addrlen);
		if (len <= 0)
		{
			utils::Log::Instance().Write("Warning recvfrom\n");
		}

		int len_out = ProcessRequest(in, len, out, sizeof(out));

		sendto(fd, &out, len_out, 0, reinterpret_cast<struct sockaddr*>(&addr4), addrlen);
	}


	int DNSServer::ProcessRequest(char *in, int len_in, char *out, int len_out)
	{
		DNSRequest req(in, len_in);
		DNSResponse resp(in, len_in);
		DNSQuery q;

		eDNSError e = req.Parse(q);

		if ( e == ERR_NONE)
		{
			DNSRegister *reg = m_db.Find(q.GetName());
			len_out = resp.GenerateResponse(reg, out, len_out);
		}
		else
		{
			len_out = resp.GenerateResponse(e, out, len_out);
		}
		
		return len_out;
	}
}

