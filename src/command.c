#include "command.h"
#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wordexp.h>


int parse_command_malloc(const char *line, struct command *cmd)
{
    int result = EXIT_SUCCESS;
    size_t count = 0;
    cmd->argv = tokenize_malloc(line, " ", &count);
    cmd->argc = count;

    parse_redirection(cmd);
    result = expand_args_malloc(cmd);
    return result;
}

void free_command(struct command *cmd)
{
    for (size_t i = 0; i < cmd->argc; ++i) {
        free(cmd->argv[i]);
        cmd->argv[i] = NULL;
    }
    free(cmd->argv);
    cmd->argv = NULL;

    if (cmd->args_to_exec != NULL) {
        int i = 0;
        while (cmd->args_to_exec[i] != NULL) {
            free(cmd->args_to_exec[i]);
            cmd->args_to_exec[i] = NULL;
            i++;
        }
        free(cmd->args_to_exec);
        cmd->args_to_exec = NULL;
    }
}

char* get_redirection_filename(char** args, size_t current_index, char* ptr)
{
    char* ret = NULL;
    if (*(ptr + 1) == '\0') {
        if (args[current_index + 1] != NULL) {
            ret = args[current_index + 1];
        }
    } else {
        ret = ptr + 1;
    }
    return ret;
}


void parse_redirection(command_t* command)      // NOLINT(readability-function-cognitive-complexity)
{
    if (command->argc < 2) {
        return;
    }
    assert(command->argc > 1);

    for (size_t i = 1; i < command->argc; i++) {
        char* ptr = strstr(command->argv[i], "<");
        if (ptr != NULL) {
            command->stdin_file = get_redirection_filename(command->argv, i, ptr);
            continue;
        }

        ptr = strstr(command->argv[i], ">");
        if (ptr != NULL) {
            if (command->argv[i] != ptr && *(ptr - 1) == '2') {
                // stderr
                if (*(ptr + 1) == '>') {
                    command->stderr_overwrite = true;
                    ptr++;
                }
                command->stderr_file = get_redirection_filename(command->argv, i, ptr);
            } else if (command->argv[i] != ptr && *(ptr - 1) == '&') {
                // both stderr, stdout
                if (*(ptr + 1) == '>') {
                    command->stderr_overwrite = true;
                    command->stdout_overwrite = true;
                    ptr++;
                }
                command->stderr_file = get_redirection_filename(command->argv, i, ptr);
                command->stdout_file = command->stderr_file;
            } else {
                // stdout
                if (*(ptr + 1) == '>') {
                    command->stdout_overwrite = true;
                    ptr++;
                }
                command->stdout_file = get_redirection_filename(command->argv, i, ptr);
            }
        }
    }
}

int expand_args_malloc(struct command* cmd)                                     // NOLINT(readability-function-cognitive-complexity)
{
    size_t args_count = cmd->argc;
    size_t count = 0;
    cmd->args_to_exec = (char**) malloc((args_count + 1)* sizeof(char*));
    size_t max_count = args_count;

    memset(cmd->args_to_exec, 0, args_count * sizeof(char*) + 1);
    for (size_t i = 0; i < cmd->argc; i++) {
        char* src_arg = cmd->argv[i];
        if (strstr(src_arg, "<") != NULL || strstr(src_arg, ">") != NULL) {
            continue;
        }
        if ((cmd->stdin_file != NULL && strcmp(cmd->stdin_file, src_arg) == 0)
            || (cmd->stdout_file != NULL && strcmp(cmd->stdout_file, src_arg) == 0)
            || (cmd->stderr_file != NULL && strcmp(cmd->stderr_file, src_arg) == 0)) {
            continue;
        }

        wordexp_t result;
        int ret = wordexp(src_arg, &result, 0);                         // NOLINT(concurrency-mt-unsafe)
        if (ret == 0) {
            for (size_t j = 0; j < result.we_wordc; j++) {
                if (count >= max_count) {
                    max_count += max_count;
                    char** temp = realloc(cmd->args_to_exec, (max_count + 1) * sizeof(char*));
                    if (temp != NULL) {
                        cmd->args_to_exec = temp;
                    } else {
                        perror("not enough memory");
                        return EXIT_FAILURE;
                    }
                }

                char abs_path[MY_PATH_MAX] = { '\0' };
                change_to_abs_path(result.we_wordv[j], abs_path);
                size_t src_arg_size = strlen(abs_path);
                (cmd->args_to_exec)[count] = (char*) malloc(src_arg_size + 1);
                strncpy((cmd->args_to_exec)[count], abs_path, src_arg_size);
                cmd->args_to_exec[count][src_arg_size] = '\0';
                count++;
            }
        } else {
            return EXIT_FAILURE;
        }
        wordfree(&result);
    }

    (cmd->args_to_exec)[count] = NULL;
    return EXIT_SUCCESS;
}

