#define INITIAL_MAX_LINE_LEN 64

#include <stdio.h>
#include <stdlib.h>

#include "env.h"
#include "util/str.h"

Env env;

/* Initializes the global environment. */
void init_env()
{
    env = (Env) {make_hashmap()};
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

    // Success!
    return 1;
}
