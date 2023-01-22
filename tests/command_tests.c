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

TestSuite *parse_command_malloc_tests(void)
{
    TestSuite *suite;

}
