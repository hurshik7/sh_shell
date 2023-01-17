#ifndef SH_SHELL_UTIL_H
#define SH_SHELL_UTIL_H


#include <string.h>


#define DEFAULT_ARGS (10)


char** tokenize_malloc(const char* str, const char* delim, size_t* out_count);


#endif /* SH_SHELL_UTIL_H */