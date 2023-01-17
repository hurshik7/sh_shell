#include "builtins.h"
#include "command.h"
#include "execute.h"
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
            execute_command(&cmd);
            free_command(&cmd);
        }
    }

    return 0;
}
