#include "header/cmds.h"

const uint8_t B2B_RECONGITION_ID[] = {0x1, 0x3, 0x3, 0x7};
const char*   B2B_ADV_NAME = "B2B-NODE ";

uint8_t _b2b_user_type;
uint8_t _b2b_cmd_counter;
uint8_t _b2b_own_id;

void init(void) {
    _b2b_user_type = B2B_TYPE_NONE;
    _b2b_cmd_counter = 0;
    _b2b_own_id = 1;
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
