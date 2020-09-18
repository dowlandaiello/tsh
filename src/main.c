#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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

        free(input);
    }

    return 0;
}
