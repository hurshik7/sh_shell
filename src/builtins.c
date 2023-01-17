#include "builtins.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int builtin_cd(char** argv, size_t argc)
{
    if (argc < 1) {
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || (strcmp(argv[1], "~") == 0)) {
        char *homedir;
        homedir = getenv("HOME");
        if (homedir != NULL) {
            if (chdir(homedir) < 0) {
                return EXIT_FAILURE;
            }
        }
    } else {
        if (chdir(argv[1]) < 0) {
            switch (errno) {
                case EACCES:
                    printf("cd: permission denied: %s\n", argv[1]);
                    break;
                case ELOOP:
                    printf("cd: too many symbolic links: %s\n", argv[1]);
                    break;
                case ENAMETOOLONG:
                    printf("cd: file name too long: %s\n", argv[1]);
                    break;
                case ENOENT:
                    printf("cd: no such file or directory: %s\n", argv[1]);
                    break;
                case ENOTDIR:
                    printf("cd: not a directory: %s\n", argv[1]);
                    break;
                default:
                    assert("cannot be here");
            }
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
