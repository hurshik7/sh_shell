#include "tests.h"
#include "execute.h"

Describe(execute);

BeforeEach(execute) // before each test, invoke this first!
{
}

AfterEach(execute)
{
}

Ensure(execute, execute_command)
{

}

Ensure(execute, handle_exec_errno)
{

}

Ensure(execute, redirect)
{

}

TestSuite *execute_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, execute, execute_command);
    add_test_with_context(suite, execute, handle_exec_errno);
    add_test_with_context(suite, execute, redirect);

    return suite;
}
