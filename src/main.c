#include "header/cmds.h"
#include "header/recv.h"

const uint8_t B2B_RECONGITION_ID[] = {0x42, 0x69, 0x6B, 0x65};
const char   B2B_ADV_NAME[] = "B2B-NODE ";

uint8_t _b2b_user_type;
uint8_t _b2b_cmd_counter;
uint8_t _b2b_own_id;

void init(void) {
    _b2b_user_type = B2B_TYPE_MEMBER;
    _b2b_cmd_counter = 0;
    _b2b_own_id = 1;

    recv_init();
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
