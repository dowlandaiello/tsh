struct String {
	/* The maximum length of the string before being allocated (including
	a null terminator) */
	int capacity;

	/* The length of the string (excluding the null terminator) */
	int len;

	/* The contents of the string */
	char *cts;
};

/**
 * Allocates and returns space for a string.
 * Should be deallocated at the end of the string's life via
 * destroy_string.
 *
 * @param initial_capacity the initial char capacity of the string
 *
 * @return a pointer to the string
 */
struct String *make_string(int initial_capacity);

/**
 * Pushes a char onto the given string.
 *
 * @param str the string onto which the char should be pushed
 * @param c the char that should be pushed onto the string
 *
 * @return the new length of the string
 */
int push_string(struct String *str, char c);

/**
 * Pops a char from the string.
 *
 * @param str the string from which the char should be popped.
 *
 * @return the popped char
 */
char pop_string(struct String *str);

/**
 * Deallocates the string.
 *
 * @param str the string to deallocate
 */
void destroy_string(struct String *str);
