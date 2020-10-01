#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "util/str.h"
#include "exten/ps1.h"
#include "util/hashmap.h"

int main()
{
    char *test_parts[] = { "a", "b", "c", "d" };
    char str[] = "a b c d";
    char delim[] = " ";
    char **parts = split(str, delim);

    for (int i = 0; i < 4; i++)
        printf("%s\n", parts[i]);
    // assert(strcmp(test_parts[i], parts[i]));
    
    HashMap map = make_hashmap();

    put_hashmap(&map, "a", "1");
    assert(strcmp(entry_for_hashmap(&map, "a")->value, "1") == 0);

    put_hashmap(&map, "aa", "19058");
    assert(strcmp(entry_for_hashmap(&map, "aa")->value, "19058") == 0);

    return 0;
}
