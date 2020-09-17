#include <stdio.h>

#include "cmd.h"

void show_prompt()
{
    printf("λ ");

    struct String input = make_string(8);

    for (int c = getchar(); c != '\n'; c = getchar()) {
        if (c == EOF) {
            destroy_string(&input);
            printf("\n");

            return;
        }

        push_string(&input, c);
    }

    struct Cmd cmd = parse_cmd(&input);
    int ret_status = execute_cmd(&cmd);
    
    if (ret_status == -1)
        return show_prompt();

    destroy_cmd(&cmd);

    if (ret_status == 1)
        return;

    show_prompt();
}

int main()
{
    show_prompt();

    return 0;
}
