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
    // TODO
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
    // TODO 여기서부터

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
