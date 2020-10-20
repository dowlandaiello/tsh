#include "cmd.h"

/**
 * A command that prints out some info about the shell.
 *
 * @param cmd the cmd
 *
 * @return the status code
 */
Res about(Cmd *cmd);

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

/**
 * Pushes a new path to the path stack.
 *
 * @param cmd the command specifying what path to add to the stack
 *
 * @return the status code
 */
Res pushd(Cmd *cmd);

/**
 * Pops a path from the path stack.
 *
 * @param cmd the command
 *
 * @return the status code
 */
Res popd(Cmd *cmd);

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
