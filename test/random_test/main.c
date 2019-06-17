#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"

static const shell_command_t _commands[] = {
    { NULL, NULL, NULL }
};

char stack[THREAD_STACKSIZE_DEFAULT];


int main(void) {

    puts("module test\n");

    /* run shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}