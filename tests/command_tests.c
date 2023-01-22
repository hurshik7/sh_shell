#include "tests.h"
#include "command.h"

Describe(command);

BeforeEach(command) // before each test, invoke this first!
{
}

AfterEach(command)
{
}

Ensure(command, parse_command_malloc)
{

}

Ensure(command, free_command)
{

}

Ensure(command, get_redirection_filename)
{

}

Ensure(command, parse_redirection)
{

}

Ensure(command, expand_args_malloc)
{

}

TestSuite* command_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, command, parse_command_malloc);
    add_test_with_context(suite, command, free_command);
    add_test_with_context(suite, command, get_redirection_filename);
    add_test_with_context(suite, command, parse_redirection);
    add_test_with_context(suite, command, expand_args_malloc);

    return suite;
}
