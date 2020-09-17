#include <assert.h>
#include <stdio.h>

#include "cmd.h"

int main()
{
    struct ArgList args = make_arg_list();

    for (int i = 0; i < 69; i++) {
        struct String arg = make_string(1);
        push_string(&arg, 'a');

        push_arg_arg_list(&args, arg);
    }

    for (int i = 0; i < args.length; i++) {
        printf("%s ", args.args[i].contents);
    }

    printf("\n");

    assert(args.length == 69);

    destroy_arg_list(&args);

    return 0;
}
