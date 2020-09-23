#include <stdlib.h>
#include <unistd.h>

#include "cmd.h"
#include "util/string.h"

/**
 * Parses a command from the provided string input.
 *
 * @param input the string that should be parsed into a command
 *
 * @return the parsed command
 */
Cmd parse_cmd(char *input){ Cmd cmd = }

/**
 * Executes the given command by forking and waiting for the command to finish
 * executing.
 */
Res exec(char *cmd, char *args)
{
    int argc = 0;

    for (int i = 0; args[i] != '\0'; i++)
        if (args[i] == ' ')
            argc++;

    char **argv = malloc(sizeof(char) * (argc + 1));

    // Spawn a child and wait for the cmd to execute
    if (fork() == 0) {
        execl(cmd, args);
    }
}
