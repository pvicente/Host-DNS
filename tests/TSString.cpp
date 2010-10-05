#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <String.hpp>
#include <string.h>

class TSString: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSString );
	CPPUNIT_TEST( MainTest );
	CPPUNIT_TEST( ConcatTest );
	CPPUNIT_TEST( SizeTest );
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

		char temp[] = "Test string";
		String stemp(temp);
		CPPUNIT_ASSERT(stemp.length() == strlen(temp));
		CPPUNIT_ASSERT(stemp == temp);
		CPPUNIT_ASSERT(strcmp(stemp.c_str(), temp) == 0);

		char temp2[]="";
		String stemp2;
		CPPUNIT_ASSERT(stemp2.length() == strlen(temp2));
		CPPUNIT_ASSERT(stemp2 == temp2);
		CPPUNIT_ASSERT(strcmp(stemp2.c_str(), temp2) == 0);
	}

	void ConcatTest()
	{
		char t1[] = "Test1";
		char t2[] = "Test2 Test3";
		char t3[strlen(t1) + strlen(t2) + 1];
		strcpy(t3, t1);
		strcat(t3, t2);

		using namespace utils;

		String res = String(t1) + String(t2);
		CPPUNIT_ASSERT(res.length() == strlen(t3));
		CPPUNIT_ASSERT(res == t3);
		CPPUNIT_ASSERT(strcmp(res.c_str(), t3) == 0);


		String res2(t1);
		res2 = res2 + t2;
		CPPUNIT_ASSERT(res2.length() == strlen(t3));
		CPPUNIT_ASSERT(res2 == t3);
		CPPUNIT_ASSERT(strcmp(res2.c_str(), t3) == 0);
	}

	void SizeTest()
	{
		using namespace utils;

		char t1[] = "Test1";
		char t2[] = "Test2 Test3";
		char t3[strlen(t1) + strlen(t2) + 1];

		strcpy(t3, t1);
		strcat(t3, t2);

		String res(strlen(t1) + strlen(t2));
		CPPUNIT_ASSERT(res.size() == strlen(t3)+1);

		String res2 = String(t1) + String(t2);
		CPPUNIT_ASSERT(res2.size() == res.size());
		CPPUNIT_ASSERT(res2 == t3);
		CPPUNIT_ASSERT(res2.length() == strlen(t3));
		CPPUNIT_ASSERT(strcmp(res2.c_str(), t3) == 0);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TSString);
#include "Main.hpp"
