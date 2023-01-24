#include "input.h"
#include "tests.h"
#include <sys/fcntl.h>
#include <unistd.h>


#define HOST_NAME_MAX_LEN (256)


static void test_get_command_line(const char* data, const char* expected_line);
static void do_test_get_command_line(const char* stream, const char* expected_line);
static void test_prompt(const char* data, const char* expected_line);
static void do_test_prompt(const char* stream, const char* expected_line);


Describe(input);

BeforeEach(input) // before each test, invoke this first!
{
}

AfterEach(input)
{
}

Ensure(input, prompt)
{
    test_prompt("ls -l\n", "ls -l");
    test_prompt("ls -l > out.txt\n", "ls -l > out.txt");
    test_prompt("ls -al 2>err.txt\n", "ls -al 2>err.txt");
    test_prompt("cat < in.txt >> out.txt\n", "cat < in.txt >> out.txt");
    test_prompt("cat < in.txt &>both.txt\n", "cat < in.txt &>both.txt");
    test_prompt("which which\n", "which which");
    test_prompt("\n", "");
    test_prompt("         \n", "");
    test_prompt("cd ..\n", "cd ..");
    test_prompt("cd ~\n", "cd ~");
    test_prompt("cd /\n", "cd /");
    test_prompt("cd \n", "cd");
    test_prompt("cd ~/Downloads\n", "cd ~/Downloads");
    test_prompt("gcc hello_world.c\n", "gcc hello_world.c");
    test_prompt("./a.out\n", "./a.out");
    test_prompt("         \n       ", "");
}

Ensure(input, prompt_ps1)
{
    int fd = open("output2.txt", O_WRONLY | O_CREAT);
    if (fd == -1) {
        perror("opening output2.txt");
        return;
    }

    int saved_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);

    char cBuf[MAX_LINE_LEN];
    char* cwd = getcwd(cBuf, sizeof(cBuf));

    prompt_ps1("", cwd);

    close(fd);
    dup2(saved_stdout, STDOUT_FILENO);

    fd = open("output2.txt", O_RDONLY);
    if (fd == -1) {
        perror("opening output2.txt");
        return;
    }

    char output[MAX_LINE_LEN];
    ssize_t read_bytes = read(fd, output, sizeof(output) - 1);
    if (read_bytes < 0) {
        perror("error: reading output2.txt");
        return;
    }
    assert_that(output, is_equal_to_string(""));
    close(fd);
}

Ensure(input, get_command_line)
{
    test_get_command_line("Hello World\n", "Hello World");
    test_get_command_line("ls -l\n", "ls -l");
    test_get_command_line("ls -l > out.txt\n", "ls -l > out.txt");
    test_get_command_line("ls -al 2>err.txt\n", "ls -al 2>err.txt");
    test_get_command_line("cat < in.txt >> out.txt\n", "cat < in.txt >> out.txt");
    test_get_command_line("cat < in.txt &>both.txt\n", "cat < in.txt &>both.txt");
    test_get_command_line("which which\n", "which which");
    test_get_command_line("\n", "");
    test_get_command_line("         \n", "");
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

static void test_get_command_line(const char* data, const char* expected_line)
{
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error creating input file\n");
        return;
    }
    fprintf(file, "%s", data);
    fclose(file);
    do_test_get_command_line("input.txt", expected_line);
}

static void do_test_get_command_line(const char* stream, const char* expected_line)
{
    char cBuf[MAX_LINE_LEN];
    int fd = open(stream, O_RDONLY);
    int saved_stdin = dup(STDIN_FILENO);

    dup2(fd, STDIN_FILENO);
    char* ret = get_command_line(cBuf);
    dup2(saved_stdin, STDIN_FILENO);

    assert_that(ret, is_equal_to_string(expected_line));
    assert_that(strcmp(cBuf, expected_line), is_equal_to(0));
    close(fd);
}

static void test_prompt(const char* data, const char* expected_line)
{
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error creating input file\n");
        return;
    }
    fprintf(file, "%s", data);
    fclose(file);
    do_test_prompt("input.txt", expected_line);
}

static void do_test_prompt(const char* stream, const char* expected_line)
{
    int wfd = open("output.txt", O_WRONLY | O_CREAT);
    if (wfd == -1) {
        perror("opening output.txt");
        return;
    }

    char cBuf[MAX_LINE_LEN];
    int fd = open(stream, O_RDONLY);
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    dup2(wfd, STDOUT_FILENO);
    dup2(fd, STDIN_FILENO);
    char* ret = prompt(cBuf);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    assert_that(ret, is_equal_to_string(expected_line));
    assert_that(strcmp(cBuf, expected_line), is_equal_to(0));
    close(fd);
    close(wfd);
}
