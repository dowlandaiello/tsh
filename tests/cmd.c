#include <assert.h>
#include <stdio.h>
#include <string.h>

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

    struct String to_parse = derive_string("a_command arg1 arg2 arg3");
    struct Cmd parsed_cmd = parse_cmd(&to_parse);

    assert(strcmp(parsed_cmd.target_program.contents, "a_command") == 0);

    for (int i = 0; i < 3; i++) {
        char arg_val[5];
        sprintf(arg_val, "arg%d", i + 1);

        assert(strcmp(parsed_cmd.args.args[i].contents, arg_val) == 0);
    }

    destroy_cmd(&parsed_cmd);

    return 0;
}

