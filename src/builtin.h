#include "cmd.h"

/**
 * WidepeepoHappy
 *
 * @param cmd the cmd
 *
 * @return the status code
 */
Res pphappy(Cmd *cmd);

/**
 * A command used to report a bug.
 *
 * @param cmd the cmd
 *
 * @return the status code
 */
Res bugreport(Cmd *cmd);

/**
 * Changes the current directory in accordance with the provided command.
 *
 * @param cmd the command specifying where to go
 *
 * @return the status code
 */
Res cd(Cmd *cmd);

/**
 * Exports an environment variable to the child process.
 *
 * @param cmd the command specifying what to export
 *
 * @return the status code
 */
Res xport(Cmd *cmd);

/* All of the available builtin commands */
typedef Res (*BuiltinCmd)(Cmd *);
extern const BuiltinCmd BUILTIN_CMDS[];

/* The names of the builtin commands */
extern const char *BUILTIN_CMD_NAMES[];

/**
 * Attempts to execute the given built-in command.
 *
 * @param cmd the command to execute as a builtin command
 *
 * @return the status code of the operation
 */
Res execute_builtin(Cmd *cmd);
