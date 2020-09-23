#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cmd.h"
#include "util/str.h"

/**
 * Parses a command from the provided string input.
 *
 * @param input the string that should be parsed into a command
 *
 * @return the parsed command
 */
Cmd parse_cmd(char *input)
{
    char **cmd_parts = split(input, " ");
    return (struct Cmd){ cmd_parts[0], cmd_parts };
}

/**
 * Deallocates the underlying string command of the given command struct.
 *
 * @param cmd the command to deallocate
 */
void destroy_cmd(Cmd *cmd)
{
    free(cmd->argv);
}

/**
 * Executes the given command by forking and waiting for the command to finish
 * executing. Does not free the command.
 */
Res exec(struct Cmd *cmd)
{
    // Anything but zero equals UH OH STINKY
    int err_shmid = shmget(IPC_PRIVATE, sizeof(unsigned int), IPC_CREAT | 0600);

    // Spawn a child and wait for the cmd to execute
    if (fork() == 0) {
        if (execv(cmd->target, cmd->argv)) {
            unsigned int *status = shmat(err_shmid, NULL, 0);

            *status = errno;
            shmdt(status);

            exit(0);
        }
    }

    wait(NULL);

    // If the child process didn't exit successfully, we will know in main to
    // log ERRNO
    unsigned int *status = shmat(err_shmid, NULL, 0);
    Res res = { *status };

    shmdt(status);
    shmctl(err_shmid, IPC_RMID, NULL);

    return res;
}
