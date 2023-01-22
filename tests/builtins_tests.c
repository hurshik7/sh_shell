#include "tests.h"
#include "builtins.h"

Describe(builtins);

BeforeEach(builtins) // before each test, invoke this first!
{
}

AfterEach(builtins)
{
}

Ensure(builtins, builtin_cd)
{

}

Ensure(builtins, builtin_which)
{

}

TestSuite* builtins_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, builtins, builtin_cd);
    add_test_with_context(suite, builtins, builtin_which);

    return suite;
}
