#include <stdio.h>

#include "common/alloc.c"

int main()
{
    // Make strings to fit up to 100 chars
    for (int i = 0; i < 100; i++) {
        // Make a string to fit 10 characters
        struct String my_string = make_string(i);

        // Force the string to allocate more space
        for (int j = 0; j <= i; j++) {
            push_string(&my_string, 'a');
        }

        printf("%s\n", my_string.contents);

        destroy_string(&my_string);
    }

    return 0;
}
