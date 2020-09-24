#define INITIAL_CAPACITY 16

/**
 * Environment variables for the shell session.
 */
typedef struct Environment {
    /* A list of keys registered in the environment */
    char **registered_keys;

    /* The values corresponding to the above keys */
    char **values;

    /* The max # of keys registerable in the environment */
    unsigned long capacity;
} Environment;

/**
 * Allocates space for an environment capable of storing 16 items at max.
 *
 * @return the allocated environment
 */
Environment make_environment();
