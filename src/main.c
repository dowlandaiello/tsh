#include <stdio.h>

#include "cmd.h"

void show_prompt()
{
    printf("> ");

    struct String input = make_string(8);

    for (int c = getchar(); c != EOF && c != '\n'; c = getchar()) {
        push_string(&input, c);
    }

    struct Cmd cmd = parse_cmd(&input);

    destroy_cmd(&cmd);

    if (execute_cmd(&cmd) == -1) {
        return;
    }

    show_prompt();
}

int main()
{
    show_prompt();

    return 0;
}
