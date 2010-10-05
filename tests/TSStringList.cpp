#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <StringList.hpp>

class TSStringList: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSStringList );
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
		using namespace utils;

		String s[3];
		s[0] = String("a");
		s[1] = String("b");
		s[2] = String("c");

		StringList l;

		CPPUNIT_ASSERT(l.size() == 0);
		CPPUNIT_ASSERT(l.empty());
		
		/* Insert Elements */
		for(std::size_t i = 0; i < sizeof(s)/sizeof(String); i++)
		{
			l.push_back(s[i]);
			CPPUNIT_ASSERT(s[i] == l.back());
		}
		
		/* Check Size */
		CPPUNIT_ASSERT(l.size() == sizeof(s)/sizeof(String));

		StringList::iterator j = l.begin();

		/* Check order */

		for(std::size_t i = 0; i < sizeof(s)/sizeof(String) && j != l.end(); i++, j++)
		{
			CPPUNIT_ASSERT(s[i] == *j);
		}
		
		/* Check Elements */

		for (std::size_t i = 0; i < sizeof(s)/sizeof(String); i++)
		{
			CPPUNIT_ASSERT(l.find(s[i]) != l.end());
		}

		/* Check Find  and Erase */
		StringList::iterator i = l.find(String("b"));
		CPPUNIT_ASSERT(*i != l.top() && *i != l.back());

		CPPUNIT_ASSERT(l.erase(i) == l.find(String("c")));

		CPPUNIT_ASSERT(l.erase(l.find("a")) == l.find(String("c")));

		l.clear();
		CPPUNIT_ASSERT(l.empty());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TSStringList);
#include "Main.hpp"
