#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Utils.hpp>
#include <string.h>

class TSUtils: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSUtils );
	CPPUNIT_TEST( MainTest );
	CPPUNIT_TEST( DecodeName );
	CPPUNIT_TEST( EncodeName );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
	}

	void tearDown()
	{
	}
	
	void MainTest()
	{
		using namespace utils;

		StringList l;

		GetInterfaceList(l);
		
		printf("Ips from interfaces up and configured:\n");
		for ( StringList::iterator i = l.begin(); i != l.end(); i++)
		{
			printf("%s\t\n", (*i).c_str() );
		}
	}

	void EncodeName()
	{
		using namespace utils;
		String name("www.google.es.");
		String encoded(name);
		
		DnsEncode(encoded);

		printf("Encoded %s:%s\n", name.c_str(), encoded.c_str());

		CPPUNIT_ASSERT(DnsEncode(name) == dns::ERR_NONE);
	}

	void DecodeName()
	{
		using namespace utils;


		char name[]="";
		TestName(name,String("."));

		char name1[]="\3www\6google\2es";
		TestName(name1, String("www.google.es."));
	}

	void TestName ( char *name , const utils::String result)
	{
		using namespace utils;

		dns::eDNSError error = dns::ERR_NONE;
		String dns_name;
		CPPUNIT_ASSERT(DnsDecode(name, strlen(name), dns_name, error) != NULL);
		
		CPPUNIT_ASSERT(error == dns::ERR_NONE );
		if (dns_name != result)
			printf("%s != %s\n", dns_name.c_str(), result.c_str());
		CPPUNIT_ASSERT(dns_name == result);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TSUtils );
#include "Main.hpp"
