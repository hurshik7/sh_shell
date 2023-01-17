#include "command.h"
#include "execute.h"
#include "util.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void execute_command(command_t* cmd)
{
    int result;
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // child process
        if (is_path(cmd->argv[0])) {
            char abs_path[PATH_MAX];
            char *res = realpath(cmd->argv[0], abs_path);
            if (res) {
                result = execv(abs_path, cmd->argv);
                if (result < 0) {
                    goto handle_err_and_exit;
                }
            }
        }

        result = execvp(cmd->argv[0], cmd->argv);
        if (result < 0) {
handle_err_and_exit:
            handle_exec_errno(cmd->argv[0]);
            cmd->exit_code = errno;
            exit(cmd->exit_code);
        }
    } else {
        // parent process
        int status;
        if (waitpid(child_pid, &status, 0) > 0) {
            if (WIFEXITED(status)) {
                printf("%d\n", WEXITSTATUS(status));
            }
        }
    }
}

void handle_exec_errno(const char* command)
{
    switch (errno) {
        case E2BIG:
            printf("%s: the argument list is too long.\n", command);
            break;
        case EACCES:
            printf("%s: permission denied.\n", command);
            break;
        case EINVAL:
            printf("%s: invalid argument.\n", command);
            break;
        case ELOOP:
            printf("%s: too many levels of symbolic links.\n", command);
            break;
        case ENAMETOOLONG:
            printf("%s: The file name is too long.\n", command);
            break;
        case ENOENT:
            printf("sh_shell: %s not found\n", command);
            break;
        case ENOTDIR:
            printf("%s: a component of the path prefix is not a directory.\n", command);
            break;
        case ENOEXEC:
            printf("%s: an attempt was made to execute a file that is not in a recognized format.\n", command);
            break;
        case ENOMEM:
            printf("%s: not enough memory.\n", command);
            break;
        case ETXTBSY:
            printf("%s: text file is busy.\n", command);
            break;
        case EFAULT:
            printf("%s: bad address.\n", command);
            break;
        case EIO:
            printf("%s: an I/O error occurred.\n", command);
            break;
        case EISDIR:
            printf("%s: an attempt was made to execute a directory.\n", command);
            break;
        case EMFILE:
            printf("%s: the process has too many files open.\n", command);
            break;
        case EPERM:
            printf("%s: the operation is not permitted.\n", command);
            break;
        case ENODEV:
            printf("%s: no such device.\n", command);
            break;
        case ENXIO:
            printf("%s: no such device or address.\n", command);
            break;
        case ESRCH:
            printf("%s: no such process.\n", command);
            break;
        default:
            printf("%s: an error occurred while executing the command (other: errno: %d).\n", command, errno);
    }
}
