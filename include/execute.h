#ifndef SH_SHELL_EXECUTE_H
#define SH_SHELL_EXECUTE_H


void execute_command(command_t* cmd);
void handle_exec_errno(const char* command);
int redirect(command_t* cmd);


#endif /* SH_SHELL_EXECUTE_H */

