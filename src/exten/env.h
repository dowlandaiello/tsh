#include "util/hashmap.h"

/**
 * An environment in which variables are stored.
 */
typedef struct Env {
	/* The variables stored in the environment */
	HashMap variables;
} Env;

/* The global environment */
extern Env env;

/* Initializes the global environment. */
void init_env();

/**
 * Loads the environment from a .env file in the immediate directory.
 *
 * @return whether or not the dotenv file was loaded successfully
 * (1 indicates success)
 */
int load_env();
