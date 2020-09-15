#include <stdlib.h>
#include <bsd/string.h>

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

	return (struct String) { initial_capacity + 1, 1, str_contents };
}

/**
 * Pushes a character to the provided string buffer.
 *
 * @param string the string to which the character should be pushed
 * @param c the character that should be pushed onto the string
 */
void push_string(struct String *string, char c)
{
	if (++string->length >= string->capacity) {
		expand_string(string, 1);		
	}
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
	char *new_contents = malloc(sizeof(char) * (string->capacity + added_capacity));

	// Expand the string
	string->capacity++;	

	// Copy the old items into the new buffer
	strcpy(new_contents, string->contents);

	// Replace the old buffer with the new buffer
	free(string->contents);
	string->contents = new_contents;

    return string->capacity;
}
