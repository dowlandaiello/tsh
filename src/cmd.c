#include <stdlib.h>

#include "cmd.h"

/**
 * Allocates a new argument list.
 */
struct ArgList make_arg_list()
{
	return (struct ArgList) {DEFAULT_ARGLIST_CAPACITY, 0, malloc(sizeof(struct String) * DEFAULT_ARGLIST_CAPACITY)};
}

/**
 * Expands the given argument list by the number of argument slots provided.
 *
 * @param added_capacity the number of argument slots that should be added to
 * the argument list
 */
void expand_arg_list(struct ArgList *args, long added_capacity)
{
        struct String *new_args = malloc(sizeof(struct String) * args->length + added_capacity);

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
 * Deallocates the argument list.
 *
 * @param args the argument list that should be deallocated
 */
void destroy_arg_list(struct ArgList *args)
{
	free(args->args);
}
