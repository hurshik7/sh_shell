#include "builtins.h"
#include "command.h"
#include "input.h"
#include "util.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH (2048)


int main(int argc, char* argv[])
{
    char command_line[MAX_LINE_LENGTH];
    int result = 0;

    while (prompt(command_line)) {
        if (command_line[0] == '\0') {
            continue;
        }

        command_t cmd;
        memset(&cmd, 0, sizeof(command_t));
        parse_command_malloc(command_line, &cmd);

        // Execute the command
        if (strcmp(cmd.argv[0], "exit") == 0) {
            free_command(&cmd);
            break;
        }
        else if (strcmp(cmd.argv[0], "cd") == 0) {
            result = builtin_cd(cmd.argv, cmd.argc);
            printf("%d\n", result);
        }
        else {
            // TODO ./a.out 이런거 가능하게 처리 -> 일단 완료, 테스트 해야함
            // TODO arguments에도 path인 값들이 있을 수 있음 -> 처리해야함
            // TODO exec 함수 errno 처리
            pid_t child_pid = fork();
            if (child_pid == 0) {
                // child process
                if (is_path(cmd.argv[0])) {
                    char abs_path[PATH_MAX];
                    char *res = realpath(cmd.argv[0], abs_path);
                    if (res) {
                        execv(abs_path, cmd.argv);
                    }
                }

                result = execvp(cmd.argv[0], cmd.argv);
                if (result < 0) {
                    printf("%s: command not found\n", cmd.argv[0]);
                    exit(0);
                }
            } else {
                // parent process
                waitpid(child_pid, NULL, 0);
                free_command(&cmd);
            }
        }
    }

    return 0;
}
