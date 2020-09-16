#include "common/alloc.h"

/* As defined in Bash on my system */
#define DEFAULT_ARGLIST_CAPACITY 9

/**
 * A list of arguments passed to a program via the tsh command line.
 */
struct ArgList {	
	/* The number of arguments that may be stored in the argument list */
	long capacity;

	/* The number of arguments currently stored in the argument list */
	long length;

	/* The argumments stored in the list of arguments */
	struct String *args;
};

/**
 * Allocates a new argument list.
 */
struct ArgList make_arg_list();

/**
 * Pushes a new argument to the argument list.
 *
 * @param args the argument list to which the argument should be pushed
 * @param arg the argument that should be pushed to the argument list
 */
void push_arg_arg_list(struct ArgList *args, struct String arg);

/**
 * Deallocates the argument list.
 *
 * @param args the argument list that should be deallocated
 */
void destroy_arg_list(struct ArgList *args);

/**
 * A tsh command passed via the command line.
 */
struct Cmd {
	/* The program targeted by the command */
	struct String target_program;

	/* Arguments to the program */
	struct ArgList args;
};
