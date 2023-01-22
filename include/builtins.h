#ifndef SH_SHELL_BUILTINS_H
#define SH_SHELL_BUILTINS_H


#include <stddef.h>


/**
 * Change the current working directory.
 * @param argv an array of strings represents arguments
 * @param argc a positive integer represents the number of arguments in argv
 * @return an integer represent the status after chdir()
 */
int builtin_cd(char** argv, size_t argc);

/**
 * Locate a program file in the user's path.
 * @param argv an array of strings represents arguments
 * @param argc a positive integer represents the number of arguments in argv
 * @return an integer represent the status after searching a program or file in the PATH
 */
int builtin_which(char** argv, size_t size);


#endif /* SH_SHELL_BUILTINS_H */

