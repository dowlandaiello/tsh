#include <assert.h>
#include <string.h>

#include "util/str.h"

int main()
{
    char *test_parts[] = {"a", "b", "c", "d"};
    char *str = "a b c d";
    char **parts = split(str, " ");

    for (int i = 0; i < 4; i++)
        assert(strcmp(test_parts[i], parts[i]));

    return 0;
}
