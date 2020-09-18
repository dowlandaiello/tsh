#include "string.h"

/**
 * Allocates and returns space for a string.
 * Should be deallocated at the end of the string's life via
 * destroy_string.
 *
 * @param initial_capacity the initial char capacity of the string
 *
 * @return a copy of the string container
 */
struct String make_string(int initial_capacity)
{
    return (struct String) { initial_capacity, 0, malloc(sizeof char * (initial_capacity + 1)) };
}
