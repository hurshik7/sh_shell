#ifndef SH_SHELL_EXECUTE_H
#define SH_SHELL_EXECUTE_H


#include "command.h"


/**
 * Execute a command.
 * @param cmd struct command
 */
void execute_command(command_t* cmd);

/**
 * Prints error messages based on errno.
 * @param command a string represents a command
 */
void handle_exec_errno(const char* command);

/**
 * Redirect I/O redirection.
 * @param cmd command struct
 * @return an integer represents the status.
 */
int redirect(command_t* cmd);


#endif /* SH_SHELL_EXECUTE_H */

