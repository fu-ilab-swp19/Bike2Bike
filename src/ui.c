#include "header/ui.h"

enum action action;
mutex_t mutex_action;

void ui_init(void) {
    mutex_init(&mutex_action);
    action = action_none;
    leds_init();
    buttons_init();
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
    led_event evt;
    evt.event_type = blink;
    evt.leds[0] = LED_LEFT_GREEN;
    evt.leds_count = 1;
    evt.event_time_ms = LEDS_CMD_LEFT_DURATION_MS;
    leds_new_event(&evt, NULL);
}

void ui_cmd_right(void) {
    printf("New command: Right\n");
    led_event evt;
    evt.event_type = blink;
    evt.leds[0] = LED_RIGHT_GREEN;
    evt.leds_count = 1;
    evt.event_time_ms = LEDS_CMD_RIGHT_DURATION_MS;
    leds_new_event(&evt, NULL);
}

void ui_cmd_stop(void) {
    printf("New command: Stop\n");
    led_event evt;
    evt.event_type = blink;
    evt.leds[0] = LED_LEFT_RED;
    evt.leds[1] = LED_RIGHT_RED;
    evt.leds_count = 2;
    evt.event_time_ms = LEDS_CMD_STOP_DURATION_MS;
    leds_new_event(&evt, NULL);
}

void ui_cmd_sync_member(void) {
    printf("Sync member\n");
    led_event evt;
    evt.event_type = blink;
    evt.leds[0] = LED_STATUS_RED;
    evt.leds_count = 1;
    evt.event_time_ms = 36000000; /* ~600 minutes */
    leds_new_event(&evt, NULL);
}

void ui_cmd_sync_member_successful(void) {
    printf("Sync member succ\n");
    leds_event_stop();
    leds_set_status_green();
}

void ui_cmd_sync_leader(void) {
    printf("Sending: Sync leader\n");
    led_event evt;
    evt.event_type = blink_color;
    evt.leds[0] = LED_STATUS_GREEN;
    evt.leds[1] = LED_STATUS_RED;
    evt.leds_count = 2;
    evt.event_time_ms = 36000000; /* ~600 minutes */
    leds_new_event(&evt, NULL);
}

void ui_cmd_sync_leader_completed(void) {
    printf("Sync leader completed\n");
    leds_event_stop();
    leds_set_status_green();
}

void ui_cmd_no_cmd(void) {
    printf("New command received: No cmd\n");
    leds_event_stop();
}

void ui_set_action(enum action new_action) {
    mutex_lock(&mutex_action);
    action = new_action;
    mutex_unlock(&mutex_action);
}

enum action ui_get_action(void) {
    mutex_lock(&mutex_action);
    enum action ret = action;
    action = action_none;
    mutex_unlock(&mutex_action);
    return ret;
}