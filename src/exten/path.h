/**
 * Resolves a path to the given target, provided that an absolute path to it is
 * located in the PATH environment variable.
 *
 * @param target the name of the program that should be resolved
 *
 * @return the absolute path to the target binary
 */
char *resolve_path(char *target);

/**
 * Recaches the PATH environment variable.
 */
void recache_path();
