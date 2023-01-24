#include "command.h"
#include "execute.h"
#include "tests.h"
#include <sys/fcntl.h>


Describe(execute);

BeforeEach(execute) // before each test, invoke this first!
{
}

AfterEach(execute)
{
}

Ensure(execute, execute_command)
{
    int wfd = open("output3.txt", O_WRONLY | O_CREAT);
    if (wfd == -1) {
        perror("opening output3.txt");
        return;
    }
    int stdout_original = dup(STDOUT_FILENO);
    dup2(wfd, STDOUT_FILENO);

    const char* user_input1 = "ls -l";
    const char* user_input2 = "ls -al > out.txt";
    const char* user_input3 = "ls";
    const char* user_input5 = "cd b.txt 2>err.txt";
    const char* user_input6 = "ls -al >> out.txt";
    const char* user_input7 = "cd b.txt 2>> err.txt";
    const char* user_input9 = "ls -al &>> both.txt";

    command_t command;
    memset(&command, 0, sizeof(command_t));
    int result = parse_command_malloc(user_input1, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(2));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-l"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-l"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input2, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-al"));
    assert_that(command.argv[2], is_equal_to_string(">"));
    assert_that(command.argv[3], is_equal_to_string("out.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-al"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input3, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(1));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input5, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(3));
    assert_that(command.argv[0], is_equal_to_string("cd"));
    assert_that(command.argv[1], is_equal_to_string("b.txt"));
    assert_that(command.argv[2], is_equal_to_string("2>err.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("cd"));
    assert_that(command.args_to_exec[1], is_equal_to_string("b.txt"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input6, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-al"));
    assert_that(command.argv[2], is_equal_to_string(">>"));
    assert_that(command.argv[3], is_equal_to_string("out.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-al"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_false);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input7, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("cd"));
    assert_that(command.argv[1], is_equal_to_string("b.txt"));
    assert_that(command.argv[2], is_equal_to_string("2>>"));
    assert_that(command.argv[3], is_equal_to_string("err.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("cd"));
    assert_that(command.args_to_exec[1], is_equal_to_string("b.txt"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_true);
    execute_command(&command);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input9, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-al"));
    assert_that(command.argv[2], is_equal_to_string("&>>"));
    assert_that(command.argv[3], is_equal_to_string("both.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-al"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("both.txt"));
    assert_that(command.stdout_file, is_equal_to_string("both.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_true);
    execute_command(&command);
    free_command(&command);

    dup2(stdout_original, STDOUT_FILENO);
    close(wfd);
}

Ensure(execute, redirect)
{
    const char* user_input1 = "ls -al > out.txt";
    const char* user_input2 = "cd b.txt 2>err.txt";
    const char* user_input3 = "ls -al >> out.txt";
    const char* user_input4 = "cd b.txt 2>> err.txt";

    command_t command;
    int result = 0;

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input1, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-al"));
    assert_that(command.argv[2], is_equal_to_string(">"));
    assert_that(command.argv[3], is_equal_to_string("out.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-al"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    result = redirect(&command);
    assert_that(result, is_equal_to(0));
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input2, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(3));
    assert_that(command.argv[0], is_equal_to_string("cd"));
    assert_that(command.argv[1], is_equal_to_string("b.txt"));
    assert_that(command.argv[2], is_equal_to_string("2>err.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("cd"));
    assert_that(command.args_to_exec[1], is_equal_to_string("b.txt"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    result = redirect(&command);
    assert_that(result, is_equal_to(0));
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input3, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("ls"));
    assert_that(command.argv[1], is_equal_to_string("-al"));
    assert_that(command.argv[2], is_equal_to_string(">>"));
    assert_that(command.argv[3], is_equal_to_string("out.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("ls"));
    assert_that(command.args_to_exec[1], is_equal_to_string("-al"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_false);
    result = redirect(&command);
    assert_that(result, is_equal_to(0));
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input4, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(4));
    assert_that(command.argv[0], is_equal_to_string("cd"));
    assert_that(command.argv[1], is_equal_to_string("b.txt"));
    assert_that(command.argv[2], is_equal_to_string("2>>"));
    assert_that(command.argv[3], is_equal_to_string("err.txt"));
    assert_that(command.args_to_exec[0], is_equal_to_string("cd"));
    assert_that(command.args_to_exec[1], is_equal_to_string("b.txt"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_true);
    result = redirect(&command);
    assert_that(result, is_equal_to(0));
    free_command(&command);
}

TestSuite *execute_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, execute, execute_command);
    add_test_with_context(suite, execute, redirect);

    return suite;
}
