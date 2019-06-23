#include "header/ui.h"

void ui_init(void) {
    leds_init();
}

void ui_cmd_changed(void) {
    switch(_b2b_current_sent_cmd) {
        case(B2B_CMD_LEFT):
            ui_cmd_left();
            break;
        case(B2B_CMD_RIGHT):
            ui_cmd_right();
            break;
        case(B2B_CMD_STOP):
            ui_cmd_stop();
            break;
        default:
            break;
    }
}

void ui_cmd_left(void) {
    printf("New command received: Left\n");
}

void ui_cmd_right(void) {
    printf("New command received: Right\n");
}

void ui_cmd_stop(void) {
    printf("New command received: Stop\n");
}

void ui_cmd_sync_member(void) {
    printf("Sync member\n");
}

void ui_cmd_sync_member_successful(void) {
    printf("Sync member succ\n");
}

void ui_cmd_sync_leader(void) {
    printf("Sync leader\n");
}

void ui_cmd_no_cmd(void) {
    printf("New command received: No cmd\n");
}
