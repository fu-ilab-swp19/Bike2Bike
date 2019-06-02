#include "header/cmds.h"

const uint8_t B2B_RECONGITION_ID[] = {0x1, 0x3, 0x3, 0x7};
const char*   B2B_AD_NAME = "B2B-NODE ";

uint8_t _b2b_user_type;
uint8_t _b2b_cmd_counter;

void init(void) {
    _b2b_user_type = B2B_TYPE_NONE;
    _b2b_cmd_counter = 0;
}

int main(void) {
    init();

    puts("Init completed\n");
    puts("Bike2Bike program started");

    // Run shell
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
