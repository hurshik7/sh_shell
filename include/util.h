#ifndef SH_SHELL_UTIL_H
#define SH_SHELL_UTIL_H


#include <string.h>


#define DEFAULT_ARGS (10)


char** tokenize_malloc(const char* str, const char* delim, size_t* out_count);
int is_path(const char *input);
void trim(char* str);


#endif /* SH_SHELL_UTIL_H */

