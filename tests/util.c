#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "util/str.h"

int main()
{
    char *test_parts[] = { "a", "b", "c", "d" };
    char str[] = "a b c d";
    char delim[] = " ";
    char **parts = split(str, delim);

    for (int i = 0; i < 4; i++)
        printf("%s\n", parts[i]);
        //assert(strcmp(test_parts[i], parts[i]));

    return 0;
}
