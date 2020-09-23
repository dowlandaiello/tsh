#include <stdio.h>
#include <string.h>

#include "str.h"

#define INITIAL_SUBSTR_PARTS_ALLOCATED 8

/**
 * Expands the given buffer if necessary.
 */
void expand(char ***parts, const int i, int *capacity)
{
    if (i < *capacity)
        return;

    char **new = malloc(sizeof(char *) * *capacity * 2);
    memcpy(new, *parts, *capacity);

    free(*parts);
    *parts = new;

    *capacity *= 2;
}

/**
 * Splits the given string into an array of strings on each occurrence of the
 * delimiter.
 *
 * @param str the string to split
 * @param delim the delimiter to split the string by
 *
 * @return the parts of the split string
 */
char **split(char *str, char *delim)
{
    /*
     * Dynamically allocate more space if more parts are found in the string
     * than expected. 8 is used as the initial capacity of the buffer.
     */
    int capacity = INITIAL_SUBSTR_PARTS_ALLOCATED, j;
    char **parts = malloc(sizeof(char *) * INITIAL_SUBSTR_PARTS_ALLOCATED);

    // Get the next token in the string before each occurrence of the delimiter
    char *saveptr, *curr_part;
    curr_part = strtok_r(str, delim, &saveptr);

    // Keep getting tokens and storing them in parts, increasing the capcaity
    // if necessary, until NULL or '\0' is hit.
    for (j = 0; curr_part != NULL;
         curr_part = strtok_r(NULL, delim, &saveptr)) {
        expand(&parts, j, &capacity);

        parts[j++] = curr_part;
    }

    expand(&parts, j, &capacity);
    parts[j] = NULL;

    return parts;
}
