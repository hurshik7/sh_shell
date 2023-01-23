#include "tests.h"
#include "util.h"

void free_string_array(char** arr);

Describe(util);

BeforeEach(util) // before each test, invoke this first!
{
}

AfterEach(util)
{
}

Ensure(util, tokenize_malloc)
{
    char input1[] = "ls -l > out.txt";
    char input2[] = "ls";
    char input3[] = "  ls";
    char input4[] = "ls  ";
    char input5[] = "ls     ";
    char input6[] = "   ls";
    char input7[] = "cat     <     in.txt  ";
    char input8[] = "Hello:world !!!";

    size_t count = 0;
    char** tokens = tokenize_malloc(input1, " ", &count);
    assert_string_equal(tokens[0], "ls");
    assert_string_equal(tokens[1], "-l");
    assert_string_equal(tokens[2], ">");
    assert_string_equal(tokens[3], "out.txt");
    assert_equal(count, 4);
    free_string_array(tokens);

    tokens = tokenize_malloc(input2, " ", &count);
    assert_equal(count, 1);
    assert_string_equal(tokens[0], "ls");
    free_string_array(tokens);

    tokens = tokenize_malloc(input3, " ", &count);
    assert_equal(count, 1);
    assert_string_equal(tokens[0], "ls");
    free_string_array(tokens);

    tokens = tokenize_malloc(input4, " ", &count);
    assert_equal(count, 1);
    assert_string_equal(tokens[0], "ls");
    free_string_array(tokens);

    tokens = tokenize_malloc(input5, " ", &count);
    assert_equal(count, 1);
    assert_string_equal(tokens[0], "ls");
    free_string_array(tokens);

    tokens = tokenize_malloc(input6, " ", &count);
    assert_equal(count, 1);
    assert_string_equal(tokens[0], "ls");
    free_string_array(tokens);

    tokens = tokenize_malloc(input7, " ", &count);
    assert_equal(count, 3);
    assert_string_equal(tokens[0], "cat");
    assert_string_equal(tokens[1], "<");
    assert_string_equal(tokens[2], "in.txt");
    free_string_array(tokens);

    tokens = tokenize_malloc(input8, " :", &count);
    assert_equal(count, 3);
    assert_string_equal(tokens[0], "Hello");
    assert_string_equal(tokens[1], "world");
    assert_string_equal(tokens[2], "!!!");
    free_string_array(tokens);
}

Ensure(util, is_path)
{
    const char* input1 = "a.out";
    const char* input2 = "./a.out";
    const char* input3 = "ls";

    int result = is_path(input1);
    assert_equal(result, 0);
    result = is_path(input2);
    assert_equal(result, 1);
    result = is_path(input3);
    assert_equal(result, 0);
}

Ensure(util, trim)
{
    char input1[] = "Hello world";
    char input2[] = " Hello world";
    char input3[] = "Hello world ";
    char input4[] = " Hello world  ";
    char input5[] = "    Hello world";
    char input6[] = "    Hello world     ";
    char input7[] = "Hello world\n";
    char input8[] = " ";
    char input9[] = "Hello";
    char input10[] = "";
    const char* expected = "Hello world";

    trim(input1);
    assert_string_equal(input1, expected);
    trim(input2);
    assert_string_equal(input2, expected);
    trim(input3);
    assert_string_equal(input3, expected);
    trim(input4);
    assert_string_equal(input4, expected);
    trim(input5);
    assert_string_equal(input5, expected);
    trim(input6);
    assert_string_equal(input6, expected);
    trim(input7);
    assert_string_equal(input7, expected);
    trim(input8);
    assert_string_equal(input8, "");
    trim(input9);
    assert_string_equal(input9, "Hello");
    trim(input10);
    assert_string_equal(input10, "");
}

Ensure(util, change_to_abs_path)
{
    char input1[MY_PATH_MAX] = "Downloads";
    char input2[MY_PATH_MAX] = "~/Downloads";
    char input3[MY_PATH_MAX] = "../../include";
    char input4[MY_PATH_MAX] = "../include";

    char output[MY_PATH_MAX];
    change_to_abs_path(input1, output);
    assert_string_equal(output, "Downloads");
    output[0] = '\0';
    change_to_abs_path(input2, output);
    assert_string_equal(output, "/Users/hurshik/Downloads");
    output[0] = '\0';
    change_to_abs_path(input3, output);
    assert_string_equal(output, "/Users/hurshik/CLionProjects/COMP4981/sh_shell/include");
    output[0] = '\0';
    change_to_abs_path(input4, output);
    assert_string_equal(output, "../include"); // since the directory does not exist.
}

Ensure(util, get_path_env_malloc_or_null)
{
    size_t count = 0;
    char** paths = get_path_env_malloc_or_null(&count);
    assert_equal(count, 15); // on my system, there are 15 tokens in PATH environment variable
    assert_string_equal(paths[0], "/usr/local/sbin");
    assert_string_equal(paths[1], "/usr/local/opt/llvm/bin");
    assert_string_equal(paths[2], "/usr/local/bin");
    assert_string_equal(paths[3], "/System/Cryptexes/App/usr/bin");
    assert_string_equal(paths[4], "/usr/bin");
    assert_string_equal(paths[5], "/bin");
    assert_string_equal(paths[6], "/usr/sbin");
    assert_string_equal(paths[7], "/sbin");
    assert_string_equal(paths[8], "/usr/local/share/dotnet");
    assert_string_equal(paths[9], "/opt/X11/bin");
    assert_string_equal(paths[10], "~/.dotnet/tools");
    assert_string_equal(paths[11], "/Library/Apple/usr/bin");
    assert_string_equal(paths[12], "/Library/Frameworks/Mono.framework/Versions/Current/Commands");
    assert_string_equal(paths[13], "/Applications/Wireshark.app/Contents/MacOS");
    assert_string_equal(paths[14], "/Applications/CLion.app/Contents/bin/ninja/mac");
    assert_equal(paths[15], NULL);

    free_string_array(paths);

    unsetenv("PATH");
    paths = get_path_env_malloc_or_null(&count);
    assert_that(paths, is_null);

    setenv("PATH", "/usr/local/sbin", true);
    paths = get_path_env_malloc_or_null(&count);
    assert_that(count, is_equal_to(1));
    assert_that(paths[0], is_equal_to_string("/usr/local/sbin"));
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

void free_string_array(char** arr)
{
    size_t count = 0;
    while (arr[count] != NULL) {
        free(arr[count]);
        arr[count++] = NULL;
    }
    free(arr);
    arr = NULL;
}

