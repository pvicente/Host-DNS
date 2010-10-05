#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <HashTable.hpp>
#include <FlatFile.hpp>

class TSHash: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSHash );
	CPPUNIT_TEST( MainTest );
	CPPUNIT_TEST( HashFileContents );
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

		HashTable l(1024);

		CPPUNIT_ASSERT(l.length() == 0);

		HashNode a("prueba1");
		HashNode b("prueba2");
		HashNode c("prueba3");

		CPPUNIT_ASSERT(l.insert(&a));
		CPPUNIT_ASSERT(l.insert(&b));
		CPPUNIT_ASSERT(l.insert(&c));

		CPPUNIT_ASSERT(l.length() == 3);

		CPPUNIT_ASSERT(l.find(a.GetKey()) == &a);
		CPPUNIT_ASSERT(l.find(b.GetKey()) == &b);
		CPPUNIT_ASSERT(l.find(c.GetKey()) == &c);

		CPPUNIT_ASSERT(l.erase(a.GetKey()) == &a);
		CPPUNIT_ASSERT(l.erase(b.GetKey()) == &b);
		CPPUNIT_ASSERT(l.erase(c.GetKey()) == &c);

		CPPUNIT_ASSERT(l.length() == 0);
	}

	void HashFileContents()
	{
		using namespace utils;
		FlatFile f("file.txt");

		HashTable t(1024);
		if (!f)
			fprintf(stderr,"file.txt don't exits. HashFileContents test not executed\n");

		uint32_t collissions = 0;
		while (!f.eof())
		{
			String s = f.GetLine();
			HashNode *n = new HashNode(s);
			CPPUNIT_ASSERT(t.insert(n));
			CPPUNIT_ASSERT(t.find(s) != NULL);
			if (t.collisions() > collissions && collissions == 0)
			{
				collissions = t.collisions();
				fprintf(stderr, "Collision with element %zd\n", f.GetNumberOfLine()) ;
			}
		}
		printf("Total Collisions %zd\n", t.collisions());

		FlatFile f1("file.txt");

		while(!f1.eof())
		{
			String s = f1.GetLine();
			CPPUNIT_ASSERT(t.find(s));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TSHash );
#include "Main.hpp"
