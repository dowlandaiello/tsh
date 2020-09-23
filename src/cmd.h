/**
 * A status code of an executed command.
 */
enum Status {
    OK,
    ERR,
};

/**
 * The result of a command's execution.
 */
typedef struct Res {
    /* The status code */
    enum Status status;
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
