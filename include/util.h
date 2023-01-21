#ifndef SH_SHELL_UTIL_H
#define SH_SHELL_UTIL_H


#include <string.h>


#define DEFAULT_ARGS (10)
#define MY_PATH_MAX (1024)


char** tokenize_malloc(const char* str, const char* delim, size_t* out_count);
int is_path(const char *input);
void trim(char* str);
int change_to_abs_path(char* filename, char abs_path[MY_PATH_MAX]);


#endif /* SH_SHELL_UTIL_H */

