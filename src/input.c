#include "input.h"
#include "util.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define HOST_NAME_MAX_LEN (256)


void* prompt(char cBuf[])
{
    void *ret;
    char *ps1 = getenv("PS1");                          // NOLINT(concurrency-mt-unsafe)
    char cwd[MY_PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    if (ps1 != NULL) {
        prompt_ps1(ps1, cwd);
    } else {
        printf("[%s] $ ", cwd);
    }
    fflush(stdout);                                     // NOLINT(cert-err33-c)

    ret = get_command_line(cBuf);
    return ret;
}

void prompt_ps1(const char* ps1, const char* cwd)
{
    char *username = getlogin();                        // NOLINT(concurrency-mt-unsafe)
    char hostname[HOST_NAME_MAX_LEN];
    gethostname(hostname, sizeof(hostname));

    const char *ptr = ps1;
    while (*ptr != '\0') {
        if (*ptr == '\\') {
            ++ptr;
            switch (*ptr) {
                case 'u':
                    printf("%s", username);
                    break;
                case 'h':
                    printf("%s", hostname);
                    break;
                case 'w':
                    printf("%s", cwd);
                    break;
                case '$':
                    if (geteuid() == 0) {
                        putchar('#');
                    } else {
                        putchar('$');
                    }
                    break;
                default:
                    putchar(*ptr);
                    break;
            }
        } else {
            putchar(*ptr);
        }
        ++ptr;
    }
}

char* get_command_line(char cBuf[])
{
    char *ret;
    ret = fgets(cBuf, MAX_LINE_LEN, stdin);
    if (ret == NULL) {
        if (ferror(stdin)) {
            printf("fgets: error reading input: %s\n", strerror(errno));            // NOLINT(concurrency-mt-unsafe)
        } else {
            printf("fgets: end of file reached\n");
        }
        printf("exit the shell. please run again\n");
        return NULL;
    }

    if (cBuf[strlen(cBuf) - 1] == '\n') {
        cBuf[strlen(cBuf) - 1] = '\0';
    }
    trim(cBuf);
    return ret;
}
