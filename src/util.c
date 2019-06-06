#include "header/util.h"

size_t util_get_own_id_length(void) {
    size_t len = 1;
    if(_b2b_own_id > 9) {
        if(_b2b_own_id > 99) {
            len = 3;
        } else {
            len = 2;
        }
    } else {
        len = 1;
    }
    return len;
}

void util_print_b2b_packet(uint8_t* data) {
    printf("Sender id: %d\n", data[0]);
    printf("Command counter: %d\n", data[1]);
    switch(data[3]) {
        case B2B_CMD_LEFT:
            printf("Command: left\n");
            break;
        case B2B_CMD_RIGHT:
            printf("Command: right\n");
            break;
        case B2B_CMD_STOP:
            printf("Command: stop\n");
            break;
        case B2B_CMD_NO_CMD:
            printf("Command: no command\n");
            break;
        case B2B_CMD_SYNC_LEADER:
            printf("Command: sync leader\n");
            break;
        case B2B_CMD_SYNC_MEMBER:
            printf("Command: sync member\n");
            break;
    }
    printf("----------------------\n");
}