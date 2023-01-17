#ifndef SH_SHELL_INPUT_H
#define SH_SHELL_INPUT_H


#define MAX_LINE_LEN (1024)


void* prompt(char cBuf[]);
void prompt_ps1(const char* ps1, const char* cwd);
char* get_command_line(char cBuf[]);


#endif /* SH_SHELL_INPUT_H */

