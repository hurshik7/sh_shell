#include "command.h"
#include "util.h"
#include <stdlib.h>


int parse_command_malloc(const char *line, struct command *cmd)
{
    // TODO redirection parsing -> darcy design 그냥 따르자. 잘 모르는거 같은데 더 제대로 하려면 복잡해짐
    // TODO wordexp() 해주기 (이때는 redirection < > 이 없는 상태, redirection 지시문 전이 \0로 바껴있음)

    size_t count = 0;
    cmd->argv = tokenize_malloc(line, " ", &count);
    cmd->argc = count;

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
}
