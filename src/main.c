#include "builtins.h"
#include "command.h"
#include "execute.h"
#include "input.h"
#include "util.h"
#include <stdio.h>


#define MAX_LINE_LENGTH (2048)


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
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
        result = parse_command_malloc(command_line, &cmd);
        if (result != 0) {
            printf("unable to parse: \"%s\"\n", command_line);
            continue;
        }

        // Execute the command
        if (strcmp(cmd.argv[0], "exit") == 0) {
            free_command(&cmd);
            break;
        }
        else if (strcmp(cmd.argv[0], "cd") == 0) {
            result = builtin_cd(cmd.argv, cmd.argc);
            printf("%d\n", result);
        }
        else if (strcmp(cmd.argv[0], "which") == 0) {
            result = builtin_which(cmd.argv, cmd.argc);
            printf("%d\n", result);
        }
        else {
            execute_command(&cmd);
        }
        free_command(&cmd);
    }

    return 0;
}
#pragma GCC diagnostic pop

