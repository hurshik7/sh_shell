#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/errno.h>
#include <assert.h>


#define MAX_LINE_LENGTH (1024)
#define MAX (255)


void* prompt(char cBuf[]);
int is_path(const char *input);


int main(int argc, char* argv[])
{
    char command_line[MAX_LINE_LENGTH];

    while (prompt(command_line)) {
        if (command_line[0] == '\0') {
            continue;
        }
        // Parse the command line into tokens
        char* command = strtok(command_line, " ");
        char* args[MAX_LINE_LENGTH] = { NULL };
        int i = 0;
        while (command != NULL) {
            args[i++] = command;
            command = strtok(NULL, " ");
        }
        args[i] = NULL;

        for (int x = 0; x < i; x++) {
            if (args[x][strlen(args[x]) - 1] == '\n') {
                args[x][strlen(args[x]) - 1] = '\0';
            }
        }

        // Execute the command
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        else if (strcmp(args[0], "cd") == 0) {
            // TODO test
            if (args[1] == NULL) {
                chdir("/");
            } else if (strcmp(args[1], "~") == 0) {
                char *homedir;
                homedir = getenv("HOME");
                if (homedir != NULL) {
                    chdir(homedir);
                }
            } else {
                if (chdir(args[1]) < 0) {
                    switch (errno) {
                        case EACCES:
                            printf("cd: permission denied: %s\n", args[1]);
                            break;
                        case ELOOP:
                            printf("cd: too many symbolic links: %s\n", args[1]);
                            break;
                        case ENAMETOOLONG:
                            printf("cd: file name too long: %s\n", args[1]);
                            break;
                        case ENOENT:
                            printf("cd: no such file or directory: %s\n", args[1]);
                            break;
                        case ENOTDIR:
                            printf("cd: not a directory: %s\n", args[1]);
                            break;
                        default:
                            assert("cannot be here");
                    }
                }
            }
        }
        else {
            // TODO ./a.out 이런거 가능하게 처리 -> 일단 완료, 테스트 해야함
            pid_t child_pid = fork();
            if (child_pid == 0) {
                // child process
                if (is_path(args[0])) {
                    char abs_path[PATH_MAX];
                    char *res = realpath(args[0], abs_path);
                    if (res) {
                        execv(abs_path, args);
                    }
                }

                int result;
                result = execvp(args[0], args);
                if (result < 0) {
                    printf("%s: command not found\n", args[0]);
                    exit(0);
                }
            } else {
                // parent process
                waitpid(child_pid, NULL, 0);
            }
        }
    }

    return 0;
}

void* prompt(char cBuf[])
{
    void *ret;
    char *ps1 = getenv("PS1");
    char *username = getlogin();
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    if (ps1 != NULL) {
        char *display_line = ps1;
        while (*display_line != '\0') {
            if (*display_line == '\\') {
                ++display_line;
                switch (*display_line) {
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
                        putchar(*display_line);
                        break;
                }
            } else {
                putchar(*display_line);
            }
            ++display_line;
        }
    } else {
        printf("[%s] $ ", cwd);
    }
    fflush(stdout);

    ret = fgets(cBuf, MAX, stdin);

    if (cBuf[strlen(cBuf)-1] == '\n') {
        cBuf[strlen(cBuf) - 1] = '\0';
    }
    return ret;
}

int is_path(const char *input)
{
    return strchr(input, '/') != NULL;
}
