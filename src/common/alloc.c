#include <stdlib.h>
#include <string.h>

#include "alloc.h"

/**
 * Creates a new String and allocates the enclosed buffer, returning the string.
 *
 * @param initial_capacity the number of characters that the String should be
 * able to store, initially
 *
 * @returns a pointer to the allocated string
 */
struct String make_string(long initial_capacity)
{
    char *str_contents = malloc(sizeof(char) * (initial_capacity + 1));
    str_contents[0] = '\0';

    return (struct String){ initial_capacity + 1, 0, str_contents };
}

/**
 * Generates a dynamic String from the provided char array.
 * NOTE: The given char array should NOT be destroyed
 * until a character is pushed to the String.
 *
 * @param s the string from which the String should be derived
 *
 * @return the string
 */
struct String derive_string(char *s)
{
    return (struct String){ 0, strlen(s), s };
}

/**
 * Deallocates the given String.
 *
 * @param string the string to deallocate
 */
void destroy_string(struct String *string)
{
    free(string->contents);
}

/**
 * Pushes a character to the provided string buffer.
 *
 * @param string the string onto which the character should be pushed
 * @param c the character that should be pushed onto the string
 */
void push_string(struct String *string, char c)
{
    if (++string->length >= string->capacity) {
        expand_string(string, 1);
    }

    string->contents[string->length - 1] = c;
    string->contents[string->length] = '\0';
}

/**
 * Adds the given number of characters to the capacity of the String.
 * NOTE: This operation is O(n) where n is the length of the String,
 * as it requires copying the old items
 *
 * @param string the string of which the capacity should be expanded
 * @param added_capacity the number of characters by which the String's
 * capacity should be increased.
 *
 * @return the new capacity of the string
 */
long expand_string(struct String *string, long added_capacity)
{
    // Allocate a new buffer to store the contents of the string
    char *new_contents =
        malloc(sizeof(char) * (string->capacity + added_capacity));

    // Expand the string
    string->capacity++;

    // Copy the old items into the new buffer
    strcpy(new_contents, string->contents);

    // Replace the old buffer with the new buffer
    free(string->contents);
    string->contents = new_contents;

    return string->capacity;
}
