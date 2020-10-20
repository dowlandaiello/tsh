#define INITIAL_MAX_LINE_LEN 64
#define NUM_ENV_PARTS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "util/str.h"

Env env, private_vars;
Stack dir_stack;

/* Initializes the global environment. */
void init_env()
{
    env = (Env){ make_hashmap(), make_hashmap(), NULL };
    private_vars = (Env){ make_hashmap(), make_hashmap(), NULL };

    dir_stack = (Stack){ NULL };
}

/* Loads the environment from a .env file in the immediate directory */
int load_env()
{
    FILE *dotenv = fopen(".env", "r");
    if (dotenv == NULL)
        return 0;

    char *line = malloc(sizeof(char) * INITIAL_MAX_LINE_LEN);
    size_t buff_size;

    for (; getline(&line, &buff_size, dotenv) != -1;) {
        /* Lines in a .env file should look like this: KEY=VALUE */
        char **line_parts = split(line, "=");

        /* Two substrings should be found for the line */
        if (line_parts[1] == NULL)
            return 0;
        put_hashmap(&env.variables, line_parts[0], line_parts[1]);
    }

    // Dump the env to an array of strings
    env.cached_dump = dump_env();

    // Success!
    return 1;
}

/**
 * Dumps the key-value entries in the environment to an array of strings.
 *
 * @return the key-value pairs in the environment
 */
char **dump_env()
{
    if (env.cached_dump != NULL)
        free(env.cached_dump);

    // Each of the entries in the hashmap
    char **vars = malloc(sizeof(char *) * env.variables.n_entries + 1);
    int j = 0;

    // Dump data in each of the hashmap's buckets
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (Entry *curr = env.variables.buckets[i].head; curr != NULL;
             curr = curr->next) {
            // Combine the key and value in the entry in the format of KEY=VALUE
            char *combined_entry = malloc(
                sizeof(char) * (strlen(curr->key) + strlen(curr->value) + 2));
            sprintf(combined_entry, "%s=%s", curr->key, curr->value);

            vars[j++] = combined_entry;
        }
    }

    vars[j] = NULL;

    return vars;
}

void destroy(Env *env)
{
    // The cached environment dump will no longer be used
    for (int i = 0; env->cached_dump != NULL && env->cached_dump[i] != NULL;
         i++)
        free(env->cached_dump[i]);

    free(env->cached_dump);

    // Manually deallocate all variables and PATH entries
    HashMap env_parts[NUM_ENV_PARTS] = { env->variables, env->path },
            curr_env_part = env_parts[0];

    for (int i = 0; i < NUM_ENV_PARTS; curr_env_part = env_parts[++i]) {
        for (int curr_bucket = 0; curr_bucket < NUM_BUCKETS; curr_bucket++) {
            for (Entry *curr = curr_env_part.buckets[curr_bucket].last;
                 curr != NULL;) {
                // Save the next node to free
                Entry *prev = curr->prev;

                // Go on to the next node
                free(curr);
                curr = prev;
            }
        }
    }
}

/**
 * Destroys the environment.
 */
void destroy_env()
{
    destroy(&env);
    destroy(&private_vars);
}
