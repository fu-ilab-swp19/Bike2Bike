#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"

int _cmd_bug(int argc, char ** argv) {
    uint32_t timeout = 9;

    if ((argc == 2) && (memcmp(argv[1], "help", 4) == 0)) {
        printf("usage: %s [timeout in ms]\n", argv[0]);
        return 0;
    }
    if (argc >= 2) {
        timeout = (uint32_t)(atoi(argv[1]) * 1000);
    }

    printf("Starting a timer for %lims\n", (timeout/1000));
    for(int i = 0; i < 200000; i++) {
        if(i%500) {
            printf("Time: %li\n", xtimer_now_usec());
        }
    }
    printf("Timer stopped\n");
    (void)argc;
    (void)argv;
    return 0;
}

static const shell_command_t _commands[] = {
    { "timer", "trigger a timer", _cmd_bug },
    { NULL, NULL, NULL }
};

int main (void) {

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}


