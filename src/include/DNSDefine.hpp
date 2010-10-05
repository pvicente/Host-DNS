#ifndef DNSDEFINE_HPP
#define DNSDEFINE_HPP

namespace dns
{
	static const std::size_t DNS_Max_Udp_Packet_Len = 512; //RFC 1035
	static const std::size_t DNS_Max_Name_Len = 512; //RFC 1035

/**
* @brief enumerated for DNS Class defined in RFC 1035
*/
	enum eCLASS
	{
		CIN=1,
		CCS,
		CCH,
		CHS,

		CANY=255
	};

/**
* @brief enumerated for DNS Type defined in RFC 1035
*/
	enum eTYPE
	{
		TA=1,
		TNS,
		TMD,
		TMF,
		TCNAME,
		TSOA,
		TMB,
		TMG,
		TMR,
		TNULL,
		TWKS,
		TPTR,
		THINFO,
		TMINFO,
		TMX,
		TTXT,

		TAXFR=252,
		TMAILB,
		TMAILA,
		TANY		
	};

/**
* @brief enumerated for DNS Response Codes defined in RFC 1035
*/
	enum eRESP
	{
		RNO_ERROR=0,
		RQUERY_FORMAT,
		RINTERNAL_FAILURE,
		RNOT_FOUND,
		RNOT_IMPLEMENTED,
		RREFUSED
	};
}

#endif

