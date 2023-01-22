#include "tests.h"
#include "input.h"

Describe(input);

BeforeEach(input) // before each test, invoke this first!
{
}

AfterEach(input)
{
}

Ensure(input, prompt)
{

}

Ensure(input, prompt_ps1)
{

}

Ensure(input, get_command_line)
{

}

TestSuite* input_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, input, prompt);
    add_test_with_context(suite, input, prompt_ps1);
    add_test_with_context(suite, input, get_command_line);

    return suite;
}
