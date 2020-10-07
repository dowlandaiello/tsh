#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "env.h"
#include "util/str.h"

/**
 * Resolves a path to the given target, provided that an absolute path to it is
 * located in the PATH environment variable.
 *
 * @param target the name of the program that should be resolved
 *
 * @return the absolute path to the target binary
 */
char *resolve_path(char *target)
{
    Entry *hit = entry_for_hashmap(&env.path, target);

    return hit != NULL ? hit->value : target;
}

/**
 * Recaches the PATH environment variable.
 */
void recache_path()
{
    Entry *e = entry_for_hashmap(&env.variables, "PATH");
    if (e == NULL)
        return;

    // Copy the value of the entry, since strtok breaks it
    char *e_val = malloc(sizeof e);
    strcpy(e_val, e->value);

    for (char *token = strtok(e_val, ":"); token != NULL;
         token = strtok(NULL, ":")) {
        // Iterate through all the files in the PATH dir
        DIR *dr = opendir(token);
        if (dr == NULL)
            return;

        // The length of the parent path
        size_t parent_path_len = strlen(token);

        for (struct dirent *de = readdir(dr); de != NULL; de = readdir(dr)) {
            // Construct a fully qualified directory for the node in the PATH
            // dir
            char *qualified_name = malloc(
                sizeof(char) * (parent_path_len + strlen(de->d_name) + 2));
            sprintf(qualified_name, "%s/%s", token, de->d_name);

            // Register an entry in the PATH for the actual binary
            put_hashmap(&env.path,
                        &qualified_name[parent_path_len + 1],
                        qualified_name);
        }

        closedir(dr);
    }

    free(e_val);
}
