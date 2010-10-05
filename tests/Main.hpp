#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <fstream>
#include <unistd.h>

void help()
{
	fprintf(stderr, " -o <fname>   Nombre del fichero de salida\n");
}

int main( int argc, char **argv)
{
	const char *fname = NULL;

	switch (getopt(argc, argv, "ho:"))
	{
	case 'o':
		fname = optarg;
		break;
	case 'h':
		help();
		return 0;
	}

	if (fname == NULL)
	{
		fprintf(stderr, "%s: fichero de salida no especificado. Consulte la ayuda con -h\n", argv[0]);
		return 1;
	}
		
	std::ofstream f(fname);
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), f, "utf8") );
	runner.run( "", false );
	return 0;
}
