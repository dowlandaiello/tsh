#include <stdio.h>

#define SHELL_MSG_PREFIX "[tsh]"

/**
 * Prints the given message with the standard shell prefix.
 *
 * @param stream the stream to which the message will be written
 * @param msg the message to log
 */
void put_shell_message(FILE *stream, char *msg);

/**
 * Handles the given ERRNO value, printing an appropriate error.
 *
 * @param err the error code to handle
 */
void log_err(unsigned int err);

/**
 * Prints the given message to the console.
 *
 * @param msg the message to print
 */
void log_info(char *msg);
