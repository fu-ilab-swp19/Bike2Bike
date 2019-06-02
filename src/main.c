#include "header/cmds.h"

int main(void) {
    puts("Yay!");

    // Run shell
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
