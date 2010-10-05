#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Tokenizer.hpp>
#include <string.h>

class TSTokenizer: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TSTokenizer );
	CPPUNIT_TEST( MainTest );
	CPPUNIT_TEST( EmptyStrAndDel );
	CPPUNIT_TEST( EmptyStr );
	CPPUNIT_TEST( WhiteDelimiters );
	CPPUNIT_TEST( NotTokens );
	CPPUNIT_TEST( NotValidDelimiter );
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
		utils::Tokenizer t("Test:Token:1:Token2", ":");
		CPPUNIT_ASSERT(t.length() == 4);
		CPPUNIT_ASSERT(strcmp(t[0], "Test") == 0);
		CPPUNIT_ASSERT(strcmp(t[1], "Token") == 0);
		CPPUNIT_ASSERT(strcmp(t[2], "1") == 0);
		CPPUNIT_ASSERT(strcmp(t[3], "Token2") == 0);
	}

	void EmptyStr()
	{
		utils::Tokenizer t("", " ");
		CPPUNIT_ASSERT(t.length() == 0);
	}

	void EmptyStrAndDel()
	{
		utils::Tokenizer t("", "");
		CPPUNIT_ASSERT(t.length() == 0);
	}


	void WhiteDelimiters()
	{
		utils::Tokenizer t("T1    T2 T3     T4T5", " ");

		CPPUNIT_ASSERT(t.length() == 4);
		CPPUNIT_ASSERT(strcmp(t[0], "T1") == 0);
		CPPUNIT_ASSERT(strcmp(t[1], "T2") == 0);
		CPPUNIT_ASSERT(strcmp(t[2], "T3") == 0);
		CPPUNIT_ASSERT(strcmp(t[3], "T4T5") == 0);
	}

	void NotTokens()
	{
		utils::Tokenizer t("T1 T2 T3 T4 T5", ":");
		CPPUNIT_ASSERT(t.length() == 1); //Character ":" is not present all string is the token
	}
	
	void NotValidDelimiter()
	{
		utils::Tokenizer t("T1 T2 T3 T4 T5", "");
		CPPUNIT_ASSERT(t.length() == 1);
	}	
};

CPPUNIT_TEST_SUITE_REGISTRATION( TSTokenizer );
#include "Main.hpp"
