#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "common/alloc.h"

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

        char* test_str = "a";

        // Make sure a char* can be converted to a String
        struct String derived_string = derive_string(test_str);
        assert(strcmp(derived_string.contents, test_str) == 0);
    }

    return 0;
}
