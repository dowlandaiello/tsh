#include "util/hashmap.h"

/**
 * An environment in which variables are stored.
 */
typedef struct Env {
	/* The variables stored in the environment */
	HashMap variables;
} Env;
