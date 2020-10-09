/**
 * An internal status code returned by a command.
 */
typedef enum InternalStatus {
    NO_DEALLOC,
    DEALLOC_ERR,
    ERR,
    OK,
} InternalStatus;

/**
 * The result of a command's execution.
 */
typedef struct Res {
    /* The status code */
    int err;

    /* An internal status code */
    InternalStatus stat;

    /* A custom error message */
    char *err_msg;
} Res;

typedef struct Cmd {
    /* The target of the cmd */
    char *target;

    /* Arguments for the target */
    char **argv;
} Cmd;

/**
 * Parses a command from the provided string input.
 *
 * @param input the string that should be parsed into a command
 *
 * @return the parsed command
 */
Cmd parse_cmd(char *input);

/**
 * Deallocates the underlying string command of the given command struct.
 *
 * @param cmd the command to deallocate
 */
void destroy_cmd(Cmd *cmd);

/**
 * Executes the given command by forking and waiting for the command to finish
 * executing.
 *
 * @param cmd the command to execute
 *
 * @return the status code of the operation
 */
Res exec(Cmd *cmd);

/**
 * Executes the given command by evaluating the PATH.
 *
 * @param cmd the command to execute
 *
 * @return the status code of the operation
 */
Res exec_path(Cmd *cmd);
