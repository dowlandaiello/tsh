#include "util/hashmap.h"
#include "util/stack.h"

/**
 * An environment in which variables are stored.
 */
typedef struct Env {
    /* The variables stored in the environment */
    HashMap variables;

    /* Variables in the PATH */
    HashMap path;

    /* A cached dump of the environment variables */
    char **cached_dump;
} Env;

/* The global environment */
extern Env env;

/* Variables unexposed to the environment */
extern Env private_vars;

/* The stack that pushd and popd deals with */
extern Stack dir_stack;

/* Commands not freed at execution time */
extern Stack builtin_cmd_residue;

/* Initializes the global environment. */
void init_env();

/**
 * Loads the environment from a .env file in the immediate directory.
 *
 * @return whether or not the dotenv file was loaded successfully
 * (1 indicates success)
 */
int load_env();

/**
 * Dumps the key-value entries in the environment to an array of strings.
 *
 * @return the key-value pairs in the environment
 */
char **dump_env();

/**
 * Destroys the environment.
 */
void destroy_env();
