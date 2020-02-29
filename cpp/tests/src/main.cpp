#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Order_T.h"
#include "MenuEntryKey_T.h"
#include "MenuEntry_T.h"
#include "Menu_T.h"
#include "Person_T.h"
#include "Guest_T.h"
#include "WorkerNode_T.h"
#include "MinHeap_T.h"
#include "Queue_T.h"
#include "WorkerBulletin_T.h"

bool init_unit_test()
{
    Order_T::init_test_suite();
    MenuEntryKey_T::init_test_suite();
    MenuEntry_T::init_test_suite();
    Menu_T::init_test_suite();
    Person_T::init_test_suite();
    Guest_T::init_test_suite();
    WorkerNode_T::init_test_suite();
    MinHeap_T::init_test_suite();
    Queue_T::init_test_suite();
    WorkerBulletin_T::init_test_suite();
    return true;
}

/**
 * Boost.Test's main entry point.
 * author ajm
 * created 2/3/20
 * modified 2/28/20
 */
int main(int argc, char *argv[])
{
    return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
}