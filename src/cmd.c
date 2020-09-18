#include <unistd.h>
#include <stdlib.h>

#include "cmd.h"

/**
 * Executes the given command by forking and waiting for the command to finish
 * executing.
 */
struct Res exec(char *cmd, char *args)
{
    int argc = 0;

    for (int i = 0; args[i] != '\0'; i++)
        if (args[i] == ' ')
            argc++;

    char **argv = malloc(sizeof(char) * (argc + 1));

    // Spawn a child and wait for the cmd to execute
    if(fork() == 0) {
        execl(cmd, args);
    }
}
