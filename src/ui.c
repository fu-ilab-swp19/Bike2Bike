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

void ui_cmd_startup(void) {
    led_event evt;
    evt.event_type = blink;
    evt.leds[0] = LED_LEFT_GREEN;
    evt.leds[1] = LED_RIGHT_GREEN;
    evt.leds[2] = LED_STATUS_GREEN;
    evt.leds_count = 3;
    evt.event_time_ms = 2000;
    
    led_event succ;
    succ.event_type = flash_endless;
    succ.leds_count = 1;
    succ.event_time_ms = 10;
    succ.leds[0] = LED_STATUS_RED;
    leds_new_event(&evt, &succ);
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

void ui_test(void) {

}
