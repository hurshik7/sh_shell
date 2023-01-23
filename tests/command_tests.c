#include "tests.h"
#include "command.h"
#include "util.h"

void free_string_array(char** arr);

Describe(command);

BeforeEach(command) // before each test, invoke this first!
{
}

AfterEach(command)
{
}

Ensure(command, parse_command_malloc)
{
    const char* user_input1 = "ls -l";
    const char* user_input2 = "ls -al > out.txt";
    const char* user_input3 = "ls";
    const char* user_input4 = "./a.out";
    const char* user_input5 = "cd b.txt 2>err.txt";
    const char* user_input6 = "ls -al >> out.txt";
    const char* user_input7 = "cd b.txt 2>> err.txt";
    const char* user_input8 = "";
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
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input4, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(1));
    assert_that(command.argv[0], is_equal_to_string("./a.out"));
    assert_that(command.args_to_exec[0], is_equal_to_string("./a.out"));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
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
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    result = parse_command_malloc(user_input8, &command);
    assert_that(result, is_equal_to(0));
    assert_that(command.argc, is_equal_to(0));
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
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
    free_command(&command);
}

Ensure(command, get_redirection_filename)
{
    const char* user_input1 = "ls -al > out.txt";
    const char* user_input2 = "cd b.txt 2>err.txt";
    const char* user_input3 = "ls -al >> out.txt";
    const char* user_input4 = "cd b.txt 2>> err.txt";
    const char* user_input5 = "ls -al &>> both.txt";

    size_t count = 0;
    char** tokens = tokenize_malloc(user_input1, " ", &count);
    char* redi_filename = get_redirection_filename(tokens, 2, *(tokens + 2));
    assert_that(redi_filename, is_equal_to_string("out.txt"));
    free_string_array(tokens);

    tokens = tokenize_malloc(user_input2, " ", &count);
    redi_filename = get_redirection_filename(tokens, 2, *(tokens + 2) + 1);
    assert_that(redi_filename, is_equal_to_string("err.txt"));
    free_string_array(tokens);

    tokens = tokenize_malloc(user_input3, " ", &count);
    redi_filename = get_redirection_filename(tokens, 2, *(tokens + 2) + 1);
    assert_that(redi_filename, is_equal_to_string("out.txt"));
    free_string_array(tokens);

    tokens = tokenize_malloc(user_input4, " ", &count);
    redi_filename = get_redirection_filename(tokens, 2, *(tokens + 2) + 2);
    assert_that(redi_filename, is_equal_to_string("err.txt"));
    free_string_array(tokens);

    tokens = tokenize_malloc(user_input5, " ", &count);
    redi_filename = get_redirection_filename(tokens, 2, *(tokens + 2) + 2);
    assert_that(redi_filename, is_equal_to_string("both.txt"));
    free_string_array(tokens);
}

Ensure(command, parse_redirection)
{
    const char* user_input1 = "ls -l";
    const char* user_input2 = "ls -al > out.txt";
    const char* user_input3 = "ls";
    const char* user_input4 = "./a.out";
    const char* user_input5 = "cd b.txt 2>err.txt";
    const char* user_input6 = "ls -al >> out.txt";
    const char* user_input7 = "cd b.txt 2>> err.txt";
    const char* user_input8 = "";
    const char* user_input9 = "ls -al &>> both.txt";
    const char* user_input10 = "cat < in.txt";
    const char* user_input11 = "cat < in.txt 2> err.txt >>out.txt";

    command_t command;
    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input1, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input2, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input3, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input4, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input5, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input6, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input7, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_true);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input8, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input9, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_null);
    assert_that(command.stderr_file, is_equal_to_string("both.txt"));
    assert_that(command.stdout_file, is_equal_to_string("both.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_true);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input10, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_equal_to_string("in.txt"));
    assert_that(command.stderr_file, is_null);
    assert_that(command.stdout_file, is_null);
    assert_that(command.stdout_overwrite, is_false);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input11, " ", &command.argc);
    parse_redirection(&command);
    assert_that(command.stdin_file, is_equal_to_string("in.txt"));
    assert_that(command.stderr_file, is_equal_to_string("err.txt"));
    assert_that(command.stdout_file, is_equal_to_string("out.txt"));
    assert_that(command.stdout_overwrite, is_true);
    assert_that(command.stderr_overwrite, is_false);
    free_command(&command);
}

Ensure(command, expand_args_malloc)
{
    const char* user_input1 = "cd ~/Downloads";
    const char* user_input2 = "./a.out > out.txt ../../include";
    const char* user_input3 = "./a.out ../../src/*.c";
    int result;
    command_t command;

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input1, " ", &command.argc);
    parse_redirection(&command);
    result = expand_args_malloc(&command);
    assert_that(result, is_equal_to(0));
    assert_that(command.args_to_exec[0], is_equal_to_string("cd"));
    assert_that(command.args_to_exec[1], is_equal_to_string("/Users/hurshik/Downloads"));
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input2, " ", &command.argc);
    parse_redirection(&command);
    result = expand_args_malloc(&command);
    assert_that(result, is_equal_to(0));
    assert_that(command.args_to_exec[0], is_equal_to_string("./a.out"));
    assert_that(command.args_to_exec[1], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/include"));
    free_command(&command);

    memset(&command, 0, sizeof(command_t));
    command.argv = tokenize_malloc(user_input3, " ", &command.argc);
    parse_redirection(&command);
    result = expand_args_malloc(&command);
    assert_that(result, is_equal_to(0));
    assert_that(command.args_to_exec[0], is_equal_to_string("./a.out"));
    assert_that(command.args_to_exec[1], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/builtins.c"));
    assert_that(command.args_to_exec[2], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/command.c"));
    assert_that(command.args_to_exec[3], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/execute.c"));
    assert_that(command.args_to_exec[4], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/input.c"));
    assert_that(command.args_to_exec[5], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/main.c"));
    assert_that(command.args_to_exec[6], is_equal_to_string("/Users/hurshik/CLionProjects/COMP4981/sh_shell/src/util.c"));
    free_command(&command);
}

TestSuite* command_tests(void)
{
    TestSuite* suite;
    suite = create_test_suite();
    add_test_with_context(suite, command, parse_command_malloc);
    add_test_with_context(suite, command, get_redirection_filename);
    add_test_with_context(suite, command, parse_redirection);
    add_test_with_context(suite, command, expand_args_malloc);

    return suite;
}

