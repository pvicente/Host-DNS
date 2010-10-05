#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <FlatFile.hpp>
#include <iostream>

class TSFlatFile: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSFlatFile );
	CPPUNIT_TEST( MainTest );
	CPPUNIT_TEST( BadTest );
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

		FlatFile f1("/etc/hosts");
		CPPUNIT_ASSERT(f1);
		
		std::ifstream f2("/etc/hosts");
		CPPUNIT_ASSERT(f2);
		while(!f1.eof() && !f2.eof())
		{
			String line1(f1.GetLine());
			std::string line2;
			getline(f2, line2);
			CPPUNIT_ASSERT(line1 == line2.c_str());
		}

		CPPUNIT_ASSERT(f1.eof() == f2.eof());
	}

	void BadTest()
	{
		using namespace utils;
		FlatFile f1("/tmp");

		CPPUNIT_ASSERT(!f1);

		FlatFile f2("/dev/null");
		CPPUNIT_ASSERT(!f2);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TSFlatFile );
#include "Main.hpp"
