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
    printf("Sender id: %d\n", data[0+sizeof(_b2b_validation_value)]);
    printf("Command counter: %d\n", data[1+sizeof(_b2b_validation_value)]);
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

void util_print_uint8_hex(uint8_t data[], size_t size, char* output) {
    printf("%s", output);
    for(size_t i = 0; i < size; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}