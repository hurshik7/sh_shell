#include "builtins.h"
#include "util.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int builtin_cd(char** argv, size_t argc)
{
    if (argc < 1) {
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || (strcmp(argv[1], "~") == 0)) {
        char *homedir;
        homedir = getenv("HOME");                               // NOLINT(concurrency-mt-unsafe)
        if (homedir != NULL) {
            if (chdir(homedir) < 0) {
                return EXIT_FAILURE;
            }
        }
    } else {
        if (chdir(argv[1]) < 0) {
            switch (errno) {
                case EACCES:
                    fprintf(stderr, "cd: permission denied: %s\n", argv[1]);                // NOLINT(cert-err33-c)
                    break;
                case ELOOP:
                    fprintf(stderr, "cd: too many symbolic links: %s\n", argv[1]);          // NOLINT(cert-err33-c)
                    break;
                case ENAMETOOLONG:
                    fprintf(stderr, "cd: file name too long: %s\n", argv[1]);               // NOLINT(cert-err33-c)
                    break;
                case ENOENT:
                    fprintf(stderr, "cd: no such file or directory: %s\n", argv[1]);        // NOLINT(cert-err33-c)
                    break;
                case ENOTDIR:
                    fprintf(stderr, "cd: not a directory: %s\n", argv[1]);                  // NOLINT(cert-err33-c)
                    break;
                default:
                    assert("cannot be here");
            }
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int builtin_which(char** argv, size_t argc)
{
    assert(argv != NULL);
    if (argc < 2) {
        return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "cd") == 0 || strcmp(argv[1], "which") == 0) {
        printf("%s: sh_shell built-in command\n", argv[1]);
        return EXIT_SUCCESS;
    }

    size_t count = 0;
    char** paths = get_path_env_malloc_or_null(&count);
    if (paths == NULL) {
        perror("error getting PATH");
        return EXIT_FAILURE;
    }

    const char* command = argv[1];
    int is_found = 1;
    for (size_t i = 0; i < count; i++) {
        char temp_path[MY_PATH_MAX]; // MY_PATH_MAX == PATH_MAX, I don't want to add <limits.h> only for the PATH_MAX
        snprintf(temp_path, sizeof(temp_path), "%s/%s", paths[i], command);             // NOLINT(cert-err33-c)
        if (access(temp_path, F_OK) == 0) {
            printf("%s\n", temp_path);
            is_found = 0;
            break;
        }
    }
    if (is_found == 1) {
        fprintf(stderr, "%s not found\n", command);                                     // NOLINT(cert-err33-c)
    }

    // free paths
    size_t i = 0;
    while (paths[i] != NULL) {
        free(paths[i]);
        paths[i++] = NULL;
    }
    free(paths);
    paths = NULL;
    return is_found;
}

