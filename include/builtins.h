#ifndef SH_SHELL_BUILTINS_H
#define SH_SHELL_BUILTINS_H


#include <stddef.h>


int builtin_cd(char** argv, size_t argc);
int builtin_which(char** argv, size_t size);


#endif /* SH_SHELL_BUILTINS_H */
