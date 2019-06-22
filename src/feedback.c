#include "header/feedback.h"

void feedback_cmd_changed(void) {
    switch(_b2b_current_sent_cmd) {
        case(B2B_CMD_LEFT):
            feedback_cmd_left();
            break;
        case(B2B_CMD_RIGHT):
            feedback_cmd_right();
            break;
        case(B2B_CMD_STOP):
            feedback_cmd_stop();
            break;
        default:
            break;
    }
}

void feedback_cmd_left(void) {
    printf("New command received: Left\n");
}

void feedback_cmd_right(void) {
    printf("New command received: Right\n");
}

void feedback_cmd_stop(void) {
    printf("New command received: Stop\n");
}

void feedback_cmd_sync_member(void) {
    printf("Sync member\n");
}

void feedback_cmd_sync_member_successful(void) {
    printf("Sync member succ\n");
}

void feedback_cmd_sync_leader(void) {
    printf("Sync leader\n");
}

void feedback_cmd_no_cmd(void) {
    printf("New command received: No cmd\n");
}