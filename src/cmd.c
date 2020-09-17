#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"

/**
 * Allocates a new argument list.
 */
struct ArgList make_arg_list()
{
    return (struct ArgList) { DEFAULT_ARGLIST_CAPACITY, 0, malloc(sizeof(struct String) * DEFAULT_ARGLIST_CAPACITY) };
}

/**
 * Expands the given argument list by the number of argument slots provided.
 *
 * @param added_capacity the number of argument slots that should be added to
 * the argument list
 */
void expand_arg_list(struct ArgList* args, long added_capacity)
{
    struct String* new_args = malloc(sizeof(struct String) * args->length + added_capacity);

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
void push_arg_arg_list(struct ArgList* args, struct String arg)
{
    if (++args->length > args->capacity) {
        expand_arg_list(args, 1);
    }

    args->args[args->length - 1] = arg;
}

/**
 * Deallocates the argument list.
 *
 * @param args the argument list that should be deallocated
 */
void destroy_arg_list(struct ArgList* args)
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
struct Cmd parse_cmd(struct String* cmd)
{
    long target_len = 0;

    for (; cmd->contents[target_len] != ' ' && cmd->contents[target_len] != '\0' && target_len < cmd->length; target_len++)
        ;

    // Fetch the target of the command string (e.g., "target arg1 arg2")
    char* target = malloc(sizeof(char) * (target_len + 1));
    strncpy(target, cmd->contents, target_len);
    target[target_len] = '\0';

    struct Cmd parsed_cmd = { derive_string(target), make_arg_list() };
    struct String current_arg_buff = make_string(8);

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
void destroy_cmd(struct Cmd* cmd)
{
    destroy_arg_list(&cmd->args);
    destroy_string(&cmd->target_program);
}
