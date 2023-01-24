#include "builtins.h"
#include "command.h"
#include "tests.h"
#include <fcntl.h>
#include <limits.h>


static void test_builtin_cd(const char* user_input, const char* expected_dir, int expected_result);
static void test_builtin_which(const char* user_input, int expected_result);


Describe(builtins);

BeforeEach(builtins)
{
}

AfterEach(builtins)
{
}

Ensure(builtins, builtin_cd)
{
    const char* user_input1 = "cd /";
    const char* user_input2 = "cd ~";
    const char* user_input3 = "cd ..";
    const char* user_input4 = "cd";
    const char* user_input5 = "cd x.txt";
    const char* user_input6 = "cd dsfasdff";
    const char* user_input7 = "cd /dev/null";
    const char* user_input8 = "cd ~/Downloads";
    const char* user_input9 = "cd ../../../";

    test_builtin_cd(user_input1, "/", 0);
    test_builtin_cd(user_input2, "/Users/hurshik", 0);
    test_builtin_cd(user_input3, "/Users", 0);
    test_builtin_cd(user_input4, "/Users/hurshik", 0);
    test_builtin_cd(user_input5, NULL, 1);
    test_builtin_cd(user_input6, "/Users/hurshik", 1);
    test_builtin_cd(user_input7, NULL, 1);
    test_builtin_cd(user_input8, "/Users/hurshik/Downloads", 0);
    test_builtin_cd(user_input9, "/", 0);
}

Ensure(builtins, builtin_which)
{
    const char* user_input1 = "which cd";
    const char* user_input2 = "which which";
    const char* user_input3 = "which gcc";
    const char* user_input4 = "which g++";
    const char* user_input5 = "which asdfasdf";

    test_builtin_which(user_input1, 0);
    test_builtin_which(user_input2, 0);
    test_builtin_which(user_input3, 0);
    test_builtin_which(user_input4, 0);
    test_builtin_which(user_input5, 1);
}

TestSuite* builtins_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, builtins, builtin_cd);
    add_test_with_context(suite, builtins, builtin_which);

    return suite;
}

static void test_builtin_cd(const char* user_input, const char* expected_dir, int expected_result)
{
    command_t command;
    char* working_dir;
    char dir[PATH_MAX];
    int result = 0;

    memset(&command, 0, sizeof(command_t));
    parse_command_malloc(user_input, &command);
    result = builtin_cd(command.args_to_exec, command.argc);
    assert_that(result, is_equal_to(expected_result));
    if (result == 0) {
        working_dir = getcwd(dir, sizeof(dir));
        assert_that(working_dir, is_equal_to_string(expected_dir));
    }

    free_command(&command);
}

static void test_builtin_which(const char* user_input, int expected_result)
{
    command_t command;
    int result = 0;
    memset(&command, 0, sizeof(command_t));
    parse_command_malloc(user_input, &command);

    result = builtin_which(command.argv, command.argc);
    assert_that(result, is_equal_to(expected_result));

    free_command(&command);
}
