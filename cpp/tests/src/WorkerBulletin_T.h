#ifndef WORKERBULLETIN_T
#define WORKERBULLETIN_T

#include <boost/test/unit_test.hpp>

class WorkerBulletin_T
{
public:
    static boost::unit_test::test_suite *init_test_suite();

private:
    static void test_case1();
};

#endif // WORKERBULLETIN_T