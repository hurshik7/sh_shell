#ifndef SH_SHELL_COMMAND_H
#define SH_SHELL_COMMAND_H

#include <stdbool.h>
#include <unistd.h>


#define MAX_LINE_LENGTH (2048)


/**
 * command struct which is consist of arguments, the number of arguments, arguments to pass when call exec,
 *  stdin filename, stdout filename. stderr filename, two boolean values which are for append option, and
 *  exit code after executing the command.
 */
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


/**
 * Parse a command line.
 * @param line a string represents the input
 * @param cmd a command struct
 * @return an integer represents the status
 */
int parse_command_malloc(const char *line, struct command *cmd);

/**
 * Free all dynamic allocated memory in the command struct.
 * @param cmd command struct
 */
void free_command(struct command *cmd);

/**
 * Get a redirection filename in a string
 * @param args an array of strings contains arguments
 * @param current_index a positive integer represents the current index of args
 * @param ptr a string contains < or >
 * @return a string represents redirection filename
 */
char* get_redirection_filename(char** args, size_t current_index, char* ptr);

/**
 * Store all redirection filenames in a command line.
 * @param command command struct
 */
void parse_redirection(command_t* command);

/**
 * Expand all arguments with wordexp().
 * @param cmd command struct
 * @return an integer represents the status
 */
int expand_args_malloc(struct command* cmd);


#endif /* SH_SHELL_COMMAND_H */

