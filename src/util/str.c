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
 * Removes whitespace from the beginning and end of the string.
 */
char *trim(char *s)
{
    for (; *s != '\0' && *s == ' '; s++)
        ;

    for (char *curr = s + strlen(s) - 1; curr != NULL && *curr == ' '; curr--)
        *curr = '\0';

    return s;
}

/**
 * Gets the next substring at the next occurrence of d or d2.
 */
char *strchr_or(char *s, char *d, char *d2, int *in_quote)
{
    char *d_idx = NULL;

    // Wait until the last non-delim character has been found,
    // or until the second prioritized delimiter has occurred
    for (char *curr = s; *curr != '\0'; curr++) {
        if (*curr == *d && !*in_quote) {
            d_idx = curr;

            *curr = '\0';
        } else {
            if (d_idx != NULL) {
                break;
            }

            if (*curr == *d2) {
                *in_quote = !*in_quote;

                return curr;
            }
        }
    }

    return d_idx;
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
    // Remove padding whitespace
    str = trim(str);

    /*
     * Dynamically allocate more space if more parts are found in the string
     * than expected. 8 is used as the initial capacity of the buffer.
     */
    int capacity = INITIAL_SUBSTR_PARTS_ALLOCATED, j = 0, in_quote = 0;
    char **parts = malloc(sizeof(char *) * INITIAL_SUBSTR_PARTS_ALLOCATED),
         *curr;

    // a bunch of args
    // ^
    // | this one right here
    parts[0] = str;

    for (curr = strchr_or(str, delim, "\"", &in_quote); curr != NULL;
         curr = strchr_or(curr, delim, "\"", &in_quote)) {
        expand(&parts, j, &capacity);

        *(curr++) = '\0';

        if (!curr || *curr == '\0')
            break;

        parts[!in_quote ? ++j : j] = curr;
    }

    // Null-terminate the list
    expand(&parts, j, &capacity);
    parts[++j] = NULL;

    return parts;
}
