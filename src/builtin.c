#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "builtin.h"
#include "exten/env.h"
#include "exten/path.h"
#include "util/str.h"

#define UNRECOGNIZED_CMD_ERR "invalid command"

/* All of the available builtin commands */
const BuiltinCmd BUILTIN_CMDS[] = { NULL, bugreport, cd, NULL, xport, NULL, NULL, pphappy};

/* The names of the builtin commands */
const char *BUILTIN_CMD_NAMES[] = { "", "bugreport", "cd", "", "export", "", "", "hi"};

/**
 * A command used to report a bug.
 *
 * @param cmd the cmd
 *
 * @return the status code
 */
Res bugreport(Cmd *cmd)
{
    printf("🕵️  Nice work! Any and all bug reports are appreciated. File one here: https://github.com/dowlandaiello/tsh/issues.\n");

    return (Res){0, (InternalStatus){OK}};
}

/**
 * WidepeepoHappy
 *
 * @param cmd the cmd
 *
 * @return the status code
 */
Res pphappy(Cmd *cmd)
{
    printf("(っ◕‿◕)っ Have a great day! <3\n");

    return (Res){0, (InternalStatus){OK}};
}

/**
 * Changes the current directory in accordance with the provided command.
 *
 * @param cmd the command specifying where to go
 *
 * @return the status code
 */
Res cd(Cmd *cmd)
{
    if (cmd->argv[1] == NULL)
        return (Res){ 0, (InternalStatus){ OK } };

    return (Res){ chdir(cmd->argv[1]) ? errno : 0, (InternalStatus){ ERR } };
}

/**
 * Exports an environment variable to the child process.
 *
 * @param cmd the command specifying what to export
 *
 * @return the status code
 */
Res xport(Cmd *cmd)
{
    if (cmd->argv[1] == NULL) {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            for (Entry *curr = env.variables.buckets[i].head; curr != NULL;
                 curr = curr->next)
                printf("%s=%s\n", curr->key, curr->value);
        }

        return (Res){ 0, (InternalStatus){ OK } };
    }

    /* Argument to export should be: KEY=VALUE */
    char **xprt_entry_parts = split(cmd->argv[1], "=");
    if (xprt_entry_parts[1] == NULL)
        return (Res){ -1,
                      (InternalStatus){ ERR },
                      "not enough arguments (KEY=VALUE expected)" };

    put_hashmap(&env.variables, xprt_entry_parts[0], xprt_entry_parts[1]);

    env.cached_dump = dump_env();
    recache_path();

    return (Res){ 0, (InternalStatus){ NO_DEALLOC } };
}

/**
 * Attempts to execute the given built-in command.
 *
 * @param cmd the command to execute as a builtin command
 *
 * @return the status code of the operation
 */
Res execute_builtin(Cmd *cmd)
{
    // All commands have a unique first letter
    //
    // Thus, it can be used to figure out which command should be run
    int cmd_num = (toupper(cmd->target[0]) - 65) %
                  (sizeof BUILTIN_CMD_NAMES / sizeof(char *));

    // But should be double checked
    if (strcmp(BUILTIN_CMD_NAMES[cmd_num], cmd->target) == 0)
        return BUILTIN_CMDS[cmd_num](cmd);

    char *err = malloc(sizeof UNRECOGNIZED_CMD_ERR + sizeof cmd->target);
    sprintf(err, "%s: %s", UNRECOGNIZED_CMD_ERR, cmd->target);

    return (Res){ -1, (InternalStatus){ ERR }, err };
}
