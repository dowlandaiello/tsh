/**
 * A status code of an executed command.
 */
enum Status {
	OK, ERR,
};

/**
 * The result of a command's execution.
 */
struct Res {
	/* The status code */
	enum Status status;	
};

/**
 * Executes the given command by forking and waiting for the command to finish
 * executing.
 */
struct Res exec(char *cmd, char *args);
