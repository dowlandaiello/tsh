#include "cmd.h"

/**
 * Changes the current directory in accordance with the provided command.
 *
 * @param cmd the command specifying where to go
 *
 * @return the status code
 */
Res cd(Cmd *cmd);

/* All of the available builtin commands */
Res (*const BUILTIN_CMDS[])(Cmd*) = {&cd};

/**
 * Attempts to execute the given built-in command.
 *
 * @param cmd the command to execute as a builtin command
 *
 * @return the status code of the operation
 */
 Res execute_builtin(Cmd *cmd);
