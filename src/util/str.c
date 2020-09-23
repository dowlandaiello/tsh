#include <string.h>

#include "str.h"

#define INITIAL_SUBSTR_PARTS_ALLOCATED 8

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
    int capacity = INITIAL_SUBSTR_PARTS_ALLOCATED;

    char **parts = malloc(sizeof(char *) * INITIAL_SUBSTR_PARTS_ALLOCATED);
    char *curr_part = strtok(str, " ");

    for (int i = 0, j = 0; str[i] != '\0' && curr_part != NULL;
         curr_part = strtok(str + i, " "), i += strlen(curr_part), j++) {
        if (j >= capacity) {
            char **new_parts = malloc(sizeof(char *) * capacity * 2);
            memcpy(new_parts, parts, capacity);

            free(parts);
            parts = new_parts;

            capacity *= 2;
        }

        parts[j] = curr_part;
    }

    return parts;
}
