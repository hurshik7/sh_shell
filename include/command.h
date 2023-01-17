#ifndef SH_SHELL_COMMAND_H
#define SH_SHELL_COMMAND_H

#include <stdbool.h>
#include <unistd.h>


#define MAX_LINE_LENGTH (2048)
#define ERROR_REDIRECT_FILE_NAME_MISSING (1)



typedef struct command
{
    size_t argc;
    char **argv;
    char *stdin_file;
    char *stdout_file;
    bool stdout_overwrite;
    char *stderr_file;
    bool stderr_overwrite;
    int exit_code;
} command_t;


int parse_command_malloc(const char *line, struct command *cmd);
void free_command(struct command *cmd);

#endif /* SH_SHELL_COMMAND_H */
