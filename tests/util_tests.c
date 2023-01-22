#include "tests.h"
#include "util.h"

Describe(util);

BeforeEach(util) // before each test, invoke this first!
{
}

AfterEach(util)
{
}

Ensure(util, tokenize_malloc)
{

}

Ensure(util, is_path)
{

}

Ensure(util, trim)
{

}

Ensure(util, change_to_abs_path)
{

}

Ensure(util, get_path_env_malloc_or_null)
{

}

TestSuite* util_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, util, tokenize_malloc);
    add_test_with_context(suite, util, is_path);
    add_test_with_context(suite, util, trim);
    add_test_with_context(suite, util, change_to_abs_path);
    add_test_with_context(suite, util, get_path_env_malloc_or_null);

    return suite;
}
