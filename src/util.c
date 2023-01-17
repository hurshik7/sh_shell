#include "util.h"
#include <stdlib.h>
#include <ctype.h>

char** tokenize_malloc(const char* str, const char* delim, size_t* out_count)
{
    char* temp_str;
    char* token;
    size_t str_length = strlen(str);
    size_t word_count = 0;
    size_t ret_size = DEFAULT_ARGS;
    size_t word_length = 0;
    char** ret;
    void* temp = NULL;

    temp_str = malloc((str_length + 1) * sizeof(char));
    strcpy(temp_str, str);

    ret = malloc(ret_size * sizeof(char*));

    token = strtok(temp_str, delim);
    if (token == NULL) {
        ret[0] = NULL;
        goto free_and_exit;
    }

    while (token != NULL) {
        word_count++;
        word_length = strlen(token);

        if (word_count == ret_size - 1) {
            ret_size += ret_size;
            temp = realloc(ret, ret_size * sizeof(char*));
            if (temp != NULL) {
                ret = temp;
            }
        }
        ret[word_count - 1] = malloc((word_length + 1) * sizeof(char));
        strcpy(ret[word_count - 1], token);
        if (ret[word_count - 1][strlen(ret[word_count - 1]) - 1] == '\n') {
            ret[word_count - 1][strlen(ret[word_count - 1]) - 1] = '\0';
        }

        token = strtok(NULL, delim);
    }

    ret[word_count] = NULL;
    *out_count = word_count;

free_and_exit:
    free(temp_str);
    temp_str = NULL;
    return ret;
}

int is_path(const char *input)
{
    return strchr(input, '/') != NULL;
}

void trim(char* str)
{
    int i = 0;
    int j = 0;
    while (isspace(str[i])) {
        i++;
    }

    if (str[i] == '\0') {
        str[0] = '\0';
        return;
    }

    while (str[i]) {
        str[j++] = str[i++];
    }
    while (isspace(str[--j])) {
        str[j] = '\0';
    }
}
