#ifndef SH_SHELL_COMMAND_H
#define SH_SHELL_COMMAND_H

#include <stdbool.h>
#include <unistd.h>


#define MAX_LINE_LENGTH (2048)



typedef struct command
{
    size_t argc;
    char **argv;
    char **args_to_exec;
    char *stdin_file;
    char *stdout_file;
    bool stdout_overwrite;
    char *stderr_file;
    bool stderr_overwrite;
    int exit_code;
} command_t;


int parse_command_malloc(const char *line, struct command *cmd);
void free_command(struct command *cmd);
char* get_redirection_filename(char** args, size_t current_index, char* ptr);
void parse_redirection(command_t* command);
int expand_args_malloc(struct command* cmd);


#endif /* SH_SHELL_COMMAND_H */
