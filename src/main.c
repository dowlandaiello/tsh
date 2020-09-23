#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#include "cmd.h"

int main()
{
    // Let readline handle path completion
    rl_bind_key('\t', rl_complete);

    for (;;) {
        char *input = readline("λ ");

        // "exit" or ^d means the shell should stop
        if (!input || strcmp(input, "exit") == 0)
            break;

        // Thanks, readline
        add_history(input);

        struct Cmd cmd = parse_cmd(input);
        struct Res res = exec(&cmd);

        free(input);
    }

    return 0;
}
