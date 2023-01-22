#ifndef SH_SHELL_TESTS_H
#define SH_SHELL_TESTS_H


#include <cgreen/cgreen.h>


TestSuite* builtins_tests(void);
TestSuite* command_tests(void);
TestSuite* execute_tests(void);
TestSuite* input_tests(void);
TestSuite* util_tests(void);


#endif //SH_SHELL_TESTS_H
