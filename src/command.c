#include "command.h"
#include "util.h"
#include <stdlib.h>


int parse_command_malloc(const char *line, struct command *cmd)
{

    size_t count = 0;
    cmd->argv = tokenize_malloc(line, " ", &count);
    cmd->argc = count;

    // TODO redirection parsing -> 완료 -> iterm꺼에서 가져다 쓰기
    // TODO wordexp(): command->argv 돌면서 다시 malloc, free하면서 wordexp() 하는데 여러개 나오면 추가하고, < Or > 가 들어가거나 or redirect_file들과 strcmp값이 0이면 제
    // TODO command_t에 char** 형 하나 추가해야 할듯! 그러면 여기서 할일은 끝!

    // TODO redirect() 함수 적절한 파일에 만들고 dup2() 할 때 redirection_filename을 realpath()돌려서 Open하기!

    return 0;
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
