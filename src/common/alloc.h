/**
 * A dynamic-length datatype representing a String.
 */
struct String {
    /* The number of characters storable in the string */
    long capacity;

    /* The number of characters in the string */
    long length;

    /* The constituent characters of the string */
    char *contents;
};

/**
 * Creates a new String and allocates the enclosed buffer, returning the string.
 *
 * @param initial_capacity the number of characters that the String should be
 * able to store, initially
 *
 * @return the string
 */
struct String make_string(long initial_capacity);

/**
 * Generates a dynamic String from the provided char array.
 *
 * @param s the string from which the String should be derived
 *
 * @return the string
 */
struct String derive_string(char *s);

/**
 * Deallocates the given String.
 *
 * @param string the string to deallocate
 */
void destroy_string(struct String *string);

/**
 * Pushes a character to the provided string buffer.
 *
 * @param string the string to which the character should be pushed
 * @param c the character that should be pushed onto the string
 */
void push_string(struct String *string, char c);

/**
 * Adds the given number of characters to the capacity of the String.
 * NOTE: This operation is O(n) where n is the length of the String,
 * as it requires copying the old items
 *
 * @param string the string of which the capacity should be expanded
 * @param added_capacity the number of characters by which the String's
 * capacity should be increased.
 */
long expand_string(struct String *string, long added_capacity);
