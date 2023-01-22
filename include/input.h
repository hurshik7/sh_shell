#ifndef SH_SHELL_INPUT_H
#define SH_SHELL_INPUT_H


#define MAX_LINE_LEN (1024)


/**
 * Prints current working directory and PS1 if it set or $ and get user input.
 * @param cBuf a char array which the user input will be stored
 * @return a string represents trimmed user input or NULL
 */
void* prompt(char cBuf[]);

/**
 * Prompt PS1.
 * @param ps1 a string represents PS1
 * @param cwd a string represents the current working directory
 */
void prompt_ps1(const char* ps1, const char* cwd);

/**
 * Get a user input from stdin.
 * @param cBuf a char array which the user input will be stored
 * @return a string represents trimmed user input
 */
char* get_command_line(char cBuf[]);


#endif /* SH_SHELL_INPUT_H */

