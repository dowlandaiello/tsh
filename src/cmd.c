#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#include "cmd.h"

/**
 * Allocates a new argument list.
 */
struct ArgList make_arg_list()
{
    return (struct ArgList){ DEFAULT_ARGLIST_CAPACITY,
                             0,
                             calloc(DEFAULT_ARGLIST_CAPACITY,
                                    sizeof(struct String)) };
}

/**
 * Expands the given argument list by the number of argument slots provided.
 *
 * @param added_capacity the number of argument slots that should be added to
 * the argument list
 */
void expand_arg_list(struct ArgList *args, long added_capacity)
{
    struct String *new_args =
        malloc(sizeof(struct String) * args->length + added_capacity);

    for (int i = 0; i < args->length; i++) {
        new_args[i] = args->args[i];
    }

    free(args->args);

    args->capacity += added_capacity;
    args->args = new_args;
}

/**
 * Pushes a new argument to the argument list.
 *
 * @param args the argument list to which the argument should be pushed
 * @param arg the argument that should be pushed to the argument list
 */
void push_arg_arg_list(struct ArgList *args, struct String arg)
{
    if (++args->length > args->capacity) {
        expand_arg_list(args, 1);
    }

    args->args[args->length - 1] = arg;
}

/**
 * Converts a list of arguments to an array of char pointers.
 *
 * NOTE: This is an O(n) operation. This can be reduced to O(1)
 * by pre-caching this conversion, but I'm too lazy to do that rn.
 *
 * @param args the argument list to convert
 *
 * @return the arguments
 */
char **to_argv(struct ArgList *args)
{
    char **argv = calloc(args->length + 1, sizeof(char *));
    int i;

    for (i = 0; i < args->length; i++)
        argv[i] = args->args[i].contents;

    // execv requires the last argument to be null
    argv[i] = NULL;

    return argv;
}

/**
 * Deallocates the argument list.
 *
 * @param args the argument list that should be deallocated
 */
void destroy_arg_list(struct ArgList *args)
{
    free(args->args);
}

/**
 * Parses a command from the given string input.
 *
 * @param cmd the string to parse into a command.
 *
 * @return the parsed command
 */
struct Cmd parse_cmd(struct String *cmd)
{
    long target_len = 0;

    for (; cmd->contents[target_len] != ' ' &&
           cmd->contents[target_len] != '\0' && target_len < cmd->length;
         target_len++)
        ;

    // Fetch the target of the command string (e.g., "target arg1 arg2")
    char *target = malloc(sizeof(char) * (target_len + 1));
    strncpy(target, cmd->contents, target_len);
    target[target_len] = '\0';

    struct Cmd parsed_cmd = { derive_string(target), make_arg_list() };
    struct String current_arg_buff = make_string(8);

    // The called script should know the name by which it was called
    push_arg_arg_list(&parsed_cmd.args, parsed_cmd.target_program);

    for (; target_len <= cmd->length; target_len++) {
        char curr = cmd->contents[target_len];

        // Once the next argument is reached, clear the arg buffer and store
        // the old one in the parsed command
        if (curr == ' ') {
            if (current_arg_buff.length > 0) {
                push_arg_arg_list(&parsed_cmd.args, current_arg_buff);
                current_arg_buff = make_string(8);
            }

            continue;
        }

        // Once a null char is found, we're done!
        if (curr == '\0' || curr == '\n') {
            if (current_arg_buff.length > 0)
                push_arg_arg_list(&parsed_cmd.args, current_arg_buff);

            break;
        }

        push_string(&current_arg_buff, curr);
    }

    return parsed_cmd;
}

/**
 * Deallocates the command.
 *
 * @param cmd the command to be deallocated.
 */
void destroy_cmd(struct Cmd *cmd)
{
    destroy_arg_list(&cmd->args);
    destroy_string(&cmd->target_program);
}

/**
 * Executes the command.
 *
 * @param cmd the command to execute.
 *
 * @return a special status code
 * -1 => skip deallocation
 *  0 => all good
 * 1 => exit terminal
 */
int execute_cmd(struct Cmd *cmd)
{
    char *raw_target = cmd->target_program.contents;

    // Convert the struct arguments to actual char arrays
    char **argv = to_argv(&cmd->args);
    int argv_empty = 0, status_code = 0;

    if (strcmp(raw_target, "exit") == 0) {
        return 1;
    } else if (strcmp(raw_target, "cd") == 0) {
        chdir(cmd->args.args[0].contents);

        return 0;
    } else if (strcmp(raw_target, "dirs") == 0) {

    } else if (strcmp(raw_target, "echo") == 0) {
        cmd->target_program.contents = "/bin/echo";
        status_code = -1;
    } else if (strcmp(raw_target, "export") == 0) {

    } else if (strcmp(raw_target, "pwd") == 0) {
        char current_path[PATH_MAX];
        printf("%s\n", getcwd(current_path, sizeof(char) * PATH_MAX));

        return 0;
    } else if (strcmp(raw_target, "ls") == 0) {
        cmd->target_program.contents = "/bin/ls";
        status_code = -1;

        if (argv[0] == NULL) {
            argv_empty = 1;

            argv[0] = ".";
        }
    }

    // Generate a child process in which the program will be run
    if (fork() == 0) {
        if (execv(cmd->target_program.contents, argv)) {
            fprintf(stderr,
                    "Unable to spawn program %s\n",
                    cmd->target_program.contents);

            exit(0);
        }
    }

    wait(NULL);

    if (argv_empty == 0)
        free(argv);

    return status_code;
}
