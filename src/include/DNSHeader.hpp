#ifndef DNS_HEADER_HPP
#define DNS_HEADER_HPP

#include <arpa/inet.h>

namespace dns
{
	/* DNS_HEADER: The DNS message header structure */
/**
* @brief Define DNS Header structure and implement inline methods to acces to header elements
*/
	struct DNSHeader
	{
		private:
		unsigned	id:16;				/* Identifier */

#if BYTE_ORDER == LITTLE_ENDIAN
		unsigned        rd :1;                          /* Recursion Desired */
		unsigned        tc :1;                          /* Truncation */
		unsigned        aa :1;                          /* Authoritative Answer */
		unsigned        opcode :4;                      /* Type of query */
		unsigned        qr :1;                          /* Query/Response flag */
		unsigned        rcode :4;                       /* Response code */
		unsigned        cd: 1;                          /* Checking Disabled */
		unsigned        ad: 1;                          /* Authentic Data */
		unsigned        z :1;				/* Unused */
		unsigned        ra :1;                          /* Recursion Available */
#else
		unsigned        qr: 1;                          /* Query/Response flag */
		unsigned        opcode: 4;                      /* Type of query */
		unsigned        aa: 1;                          /* Authoritative Answer */
		unsigned        tc: 1;                          /* Truncation */
		unsigned        rd: 1;                          /* Recursion Desired */
		unsigned        ra: 1;                          /* Recursion Available */
		unsigned        z :1;                                   /* Unused */
		unsigned        ad: 1;                          /* Authentic Data */
		unsigned        cd: 1;                          /* Checking Disabled */
		unsigned        rcode :4;                       /* Response code */
#endif
		unsigned	qdc:16;				/* Entries in question section */
		unsigned	anc:16;				/* Entries in answer section */
		unsigned	nsc:16;				/* Entries in authority records */
		unsigned	arc:16;				/* Entries in aditional records */


		public:
		uint16_t GetId(){ return ntohs(id);}
		void SetId(uint16_t p_id){ id = htons(id);}

		bool IsQuestion(){ return qr == 0; }
		bool IsResponse(){ return qr == 1; }
		void SetRequest() { qr = 0;}
		void SetResponse(){ qr = 1;}

		bool IsStandardQuery() { return opcode == 0; }
		void SetStandardQuery() { opcode = 0; }

		void SetAuthoritative(bool value) { aa = value ;}

		bool IsTruncated() { return tc == 1;}
		void SetTruncated(bool value) { tc = value;}
		void SetRecursion(bool value) {ra = value;}
		void SetRecursionDesired(bool value) { rd = value;}

		void SetResponseCode(int code){rcode = code;}

		uint16_t GetQuestions(){ return ntohs(qdc);}
		void SetQuestions(uint16_t p_questions){ qdc = htons(p_questions); }
		void SetAnswers(uint16_t p_Ansquer){ anc = htons(p_Ansquer);}
	};
}

#endif 

