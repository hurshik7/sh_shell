#include "command.h"
#include "execute.h"
#include "util.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void execute_command(command_t* cmd)
{
    int result;
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // child process
        if (redirect(cmd) != 0) {
            exit(126);
        }
        if (is_path(cmd->args_to_exec[0])) {
            char abs_path[PATH_MAX];
            char *res = realpath(cmd->args_to_exec[0], abs_path);
            if (res) {
                result = execv(abs_path, cmd->args_to_exec);
                if (result < 0) {
                    goto handle_err_and_exit;
                }
            }
        }
        result = execvp(cmd->args_to_exec[0], cmd->args_to_exec);
        if (result < 0) {
handle_err_and_exit:
            handle_exec_errno(cmd->args_to_exec[0]);
            cmd->exit_code = errno;
            exit(cmd->exit_code);
        }
    } else {
        // parent process
        int status;
        if (waitpid(child_pid, &status, 0) > 0) {
            if (WIFEXITED(status)) {
                cmd->exit_code = WEXITSTATUS(status);
                printf("%d\n", WEXITSTATUS(status));
            }
        }
    }
}

void handle_exec_errno(const char* command)
{
    switch (errno) {
        case E2BIG:
            fprintf(stderr, "%s: the argument list is too long.\n", command);
            break;
        case EACCES:
            fprintf(stderr, "%s: permission denied.\n", command);
            break;
        case EINVAL:
            fprintf(stderr, "%s: invalid argument.\n", command);
            break;
        case ELOOP:
            fprintf(stderr, "%s: too many levels of symbolic links.\n", command);
            break;
        case ENAMETOOLONG:
            fprintf(stderr, "%s: The file name is too long.\n", command);
            break;
        case ENOENT:
            fprintf(stderr, "sh_shell: %s not found\n", command);
            break;
        case ENOTDIR:
            fprintf(stderr, "%s: a component of the path prefix is not a directory.\n", command);
            break;
        case ENOEXEC:
            fprintf(stderr, "%s: an attempt was made to execute a file that is not in a recognized format.\n", command);
            break;
        case ENOMEM:
            fprintf(stderr, "%s: not enough memory.\n", command);
            break;
        case ETXTBSY:
            fprintf(stderr, "%s: text file is busy.\n", command);
            break;
        case EFAULT:
            fprintf(stderr, "%s: bad address.\n", command);
            break;
        case EIO:
            fprintf(stderr, "%s: an I/O error occurred.\n", command);
            break;
        case EISDIR:
            fprintf(stderr, "%s: an attempt was made to execute a directory.\n", command);
            break;
        case EMFILE:
            fprintf(stderr, "%s: the process has too many files open.\n", command);
            break;
        case EPERM:
            fprintf(stderr, "%s: the operation is not permitted.\n", command);
            break;
        case ENODEV:
            fprintf(stderr, "%s: no such device.\n", command);
            break;
        case ENXIO:
            fprintf(stderr, "%s: no such device or address.\n", command);
            break;
        case ESRCH:
            fprintf(stderr, "%s: no such process.\n", command);
            break;
        default:
            fprintf(stderr, "%s: an error occurred while executing the command (other: errno: %d).\n", command, errno);
    }
}

int redirect(command_t* cmd)
{
    if (cmd->stdin_file != NULL) {
        char abs_path[PATH_MAX] = { '\0' };
        if (change_to_abs_path(cmd->stdin_file, abs_path) != EXIT_SUCCESS) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
        int stdin_redirection_file;
        stdin_redirection_file = open(abs_path, O_RDONLY);
        if (stdin_redirection_file == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
        dup2(stdin_redirection_file, STDIN_FILENO);
        if (close(stdin_redirection_file) == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
    }

    if (cmd->stdout_file != NULL) {
        char abs_path[PATH_MAX] = { '\0' };
        if (change_to_abs_path(cmd->stdout_file, abs_path) != EXIT_SUCCESS) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
        int stdout_redirection_file;
        if (cmd->stdout_overwrite == true) {
            stdout_redirection_file = open(abs_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            stdout_redirection_file = open(abs_path, O_WRONLY | O_CREAT, 0644);
        }

        if (stdout_redirection_file == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }

        dup2(stdout_redirection_file, STDOUT_FILENO);
        if (close(stdout_redirection_file) == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
    }

    if (cmd->stderr_file != NULL) {
        char abs_path[PATH_MAX] = { '\0' };
        if (change_to_abs_path(cmd->stderr_file, abs_path) != EXIT_SUCCESS) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
        int stderr_redirection_file;
        if (cmd->stderr_overwrite == true) {
            stderr_redirection_file = open(abs_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            stderr_redirection_file = open(abs_path, O_WRONLY | O_CREAT, 0644);
        }

        if (stderr_redirection_file == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }

        dup2(stderr_redirection_file, STDERR_FILENO);
        if (close(stderr_redirection_file) == -1) {
            fprintf(stderr, "Error opening I/O redirection file\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
