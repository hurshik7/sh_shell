#include <limits.h>
#include <stdio.h>	// printf
#include <stdlib.h> // exit
#include <string.h> // perror, strlen
#include <sys/wait.h> // waitpid
#include <unistd.h>	// fork, chdir

#define MAX (255)

void* prompt(char cBuf[]);

int main(int argc, char* argv[])
{
    char cBuf[MAX];
    char *arg[4];
    char *arg_p[2];
    int pid, pipe_p1, pipe_p2;
    int status;
    int fd[2];

    while (prompt(cBuf)) {	// while successful input
        if ((pid=fork()) < 0) {
            perror("fork error");
        }
        else if (pid ==0) {	// child
            // 명령어 공백기준 분할
            arg[0] = strtok(cBuf," ");
            // 자른 문자 다음부터 구분자 또 찾기
            arg[1] = strtok(NULL, " ");

            if (strcmp(arg[0], "exit") == 0) {
                printf("exit sh_shell\n");
                exit(0);
                // 이거 잘 안됨. 일단 공부부터!
            }

            if (arg[1] == NULL) {					//	(1) no argument
                if (execvp(arg[0], arg) < 0) {
                    printf("%s: command not found\n",arg[0]);
                    exit(0);
                }
            }
            else if (*arg[1] != '|') {			// (2) one argument
                arg[2] = 0;
                // cd command
                if (strcmp(arg[0], "cd") == 0) {
                    chdir(arg[1]);
                }
                else {    // another command
                    if (execvp(arg[0], arg) < 0) {
                        printf("%s: command not found\n", arg[0]);
                        exit(0);
                    }
                }
            }
            else {								// (3) pipe
                arg[2] = strtok(NULL, " ");
                arg[3] = 0;

                pipe(fd);

                if ((pipe_p1=fork()) == 0) {
                    close(1);		// close stdout
                    close(fd[0]);	// close pipe read
                    dup(fd[1]);		// dup pipe write at stdout
                    close(fd[1]);

                    arg_p[0] = arg[0];
                    arg_p[1] = 0;

                    if (execvp(arg[0],arg_p) < 0) {
                        printf("%s: command not found\n", arg[0]);
                        exit(0);
                    }
                }
                else if (pipe_p1 < 0) {
                    perror("fork error");
                }

                if ((pipe_p2=fork()) == 0) {
                    close(0);		// close stdin
                    close(fd[1]);	// close piepe write
                    dup(fd[0]);		// dup pipe read at stdin
                    close(fd[0]);

                    arg_p[0] = arg[2]; arg_p[1] = 0;

                    if (execvp(arg[2],arg_p) < 0) {
                        printf("%s: command not found\n", arg[0]);
                        exit(0);
                    }

                    perror("child2 execvp failed");
                    exit(1);
                }
                else if(pipe_p2 < 0) {
                    perror("fork error");
                }
                close(fd[1]);
                close(fd[0]);
                wait(0);
                wait(0);
            }
        }

        waitpid(pid, &status, 0);
    }
    return 0;
}

void* prompt(char cBuf[])
{
    void *ret;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("sh_shell > [%s] ", cwd);
    } else {
        perror("getcwd() error");
    }

    ret = fgets(cBuf, MAX, stdin);

    if (cBuf[strlen(cBuf)-1] == '\n') {
        cBuf[strlen(cBuf) - 1] = 0;
    }
    return ret;
}
