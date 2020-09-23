#include <errno.h>
#include <string.h>

#include "log.h"

extern int errno;

/**
 * Prints the given message with the standard shell prefix.
 *
 * @param stream the stream to which the message will be written
 * @param msg the message to log
 */
void put_shell_message(FILE *stream, char *msg)
{
    fprintf(stream, "%s %s\n", SHELL_MSG_PREFIX, msg);
}

/**
 * Handles the given ERRNO value, printing an appropriate error.
 *
 * @param err the error code to handle
 */
void log_err(unsigned int err)
{
    put_shell_message(stderr, strerror(err));
}

/**
 * Prints the given message to the console.
 *
 * @param msg the message to print
 */
void log_info(char *msg)
{
    put_shell_message(stdout, msg);
}
