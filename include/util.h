#ifndef SH_SHELL_UTIL_H
#define SH_SHELL_UTIL_H


#include <string.h>


#define DEFAULT_ARGS (10)
#define MY_PATH_MAX (1024)


/**
 * Tokenize a string. It uses malloc so that the caller should free it.
 * @param str a string to tokenize
 * @param delim a string contains delimiters
 * @param out_count a pointer to unsigned integer which will store the number of tokens
 * @return an array of strings contains all tokens
 */
char** tokenize_malloc(const char* str, const char* delim, size_t* out_count);

/**
 * Returns 1 if the input string has / or 0.
 * @param input a string
 * @return 1 or 0
 */
int is_path(const char *input);

/**
 * Trim the input string.
 * @param str a string
 */
void trim(char* str);

/**
 * Expand a filename to absolute path if the filename is a path.
 * @param filename a string
 * @param abs_path a string which will store the absolute path of the file
 * @return an integer represents the status
 */
int change_to_abs_path(char* filename, char abs_path[MY_PATH_MAX]);

/**
 * Returns PATH as an array of strings. It uses malloc so that the caller should free it.
 * @param path_count_out a pointer to unsigned integer will store the number of paths
 * @return an array of strings
 */
char** get_path_env_malloc_or_null(size_t* path_count_out);


#endif /* SH_SHELL_UTIL_H */

