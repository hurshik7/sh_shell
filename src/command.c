#include "command.h"
#include "util.h"
#include <stdlib.h>


int parse_command_malloc(const char *line, struct command *cmd)
{
    size_t count = 0;
    cmd->argv = tokenize_malloc(line, " ", &count);
    cmd->argc = count;

    // TODO command line expand 해줘야함! wordexp();

    for (size_t i = 0; i < count; ++i) {
        // TODO redirect parsing

    }

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
