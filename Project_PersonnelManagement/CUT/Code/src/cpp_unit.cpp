#include <iostream>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <netinet/in.h>
#include <string>
#include "proj_func.cpp"


using namespace CppUnit;
using namespace std;

class testpersonnel: public CppUnit::TestFixture
{	
	CPPUNIT_TEST_SUITE(testpersonnel);
	CPPUNIT_TEST(test_query);
	CPPUNIT_TEST(test_addproj);
	CPPUNIT_TEST_SUITE_END();
	
	public:
		void setUp(void);
		void tearDown(void);
	protected:
		void test_query(void);
		void test_addproj(void);
	private:
		PROJECT *obj;
};

void testpersonnel::test_query(void)
{
	CPPUNIT_ASSERT(0==query());
}

void testpersonnel::test_addproj(void)
{
	CPPUNIT_ASSERT(0==addproj());
}

void testpersonnel::setUp(void)
{
	obj=new PROJECT();
}

void testpersonnel::tearDown(void)
{
	delete obj;
}

CPPUNIT_TEST_SUITE_REGISTRATION(testpersonnel);

int main(int argc,char* argv[])
{
	CPPUNIT_NS::TestResult testresult;
	CPPUNIT_NS::TestResultCollector collectedresults;
	testresult.addListener(&collectedresults);
	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener(&progress);
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults,std::cerr);
	compileroutputter.write();
	return collectedresults.wasSuccessful()?0:1;

}

