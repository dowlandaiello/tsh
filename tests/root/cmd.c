#include "cmd.h"

int main()
{
        struct ArgList args = make_arg_list();

        for (int i = 0; i < 69; i++) {
                struct String arg = make_string(1);
                push_string(&arg, 'a');

                push_arg_arg_list(&args, arg);
        }

        return 0;
}
