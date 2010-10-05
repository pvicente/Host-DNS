#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <DNSDatabase.hpp>

class TSDNSDatabase: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSDNSDatabase );
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
		DNSDatabase db;

		db.Load("/etc/hosts");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TSDNSDatabase );

#include "Main.hpp"
