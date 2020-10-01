#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

#include "exten/log.h"
#include "exten/ps1.h"
#include "exten/env.h"
#include "cmd.h"

/* The ps1 */
extern char *ps1_seq;

int main()
{
    set_ps1("λ ");

    // Load environment variables from a .env file (if it exists)
    init_env();
    load_env();

    // Let readline handle path completion
    rl_bind_key('\t', rl_complete);

    for (;;) {
        char *input = readline(ps1_seq);

        // "exit" or ^d means the shell should stop
        if (!input || strcmp(input, "exit") == 0)
            break;

        // Thanks, readline
        add_history(input);

        Cmd cmd = parse_cmd(input);
        Res res = exec(&cmd);

        if (res.err)
            log_err(res.err);

        free(input);
    }

    return 0;
}
