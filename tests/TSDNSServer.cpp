#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <DNSServer.hpp>

class TSDNSServer: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSDNSServer );
	CPPUNIT_TEST( MainTest );
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
		using namespace dns;

		DNSServer server("/etc/hosts", 53);

		server.Run();
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TSDNSServer );

#include "Main.hpp"
