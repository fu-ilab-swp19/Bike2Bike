#include "header/buttons.h"

static void check_button_actions(void);
static void reset_buttons(void);

char stack_buttons[THREAD_STACKSIZE_SMALL];

bool left_button_pressed = false;
bool right_button_pressed = false;
bool sync_button_pressed = false;
bool extra_button_pressed = false;

int press_detected = 0;

static void* thread_buttons(void* arg) {
    (void) arg;
    while(true) {
        if(left_button_pressed || right_button_pressed || sync_button_pressed 
            || extra_button_pressed) {
            if(press_detected >= 2) {
                /* now check buttons for possible actions */
                check_button_actions();

            } else {
                /* wait another wakeup, (give user some time to press another button) */
                press_detected++;
            }
        }
        /* let thread sleep, shouldn't block other threads too long */
        xtimer_usleep(BUTTONS_THREAD_SLEEP_MS);
    }
    return NULL;
}


static void check_button_actions(void) {
    if(left_button_pressed && !right_button_pressed && !sync_button_pressed
        && !extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_left);
            return;
    }
    if(!left_button_pressed && right_button_pressed && !sync_button_pressed
        && !extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_right);
            return;
    }

    if(!left_button_pressed && right_button_pressed && sync_button_pressed
        && !extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_sync_leader);
            return;
    }

    if(!left_button_pressed && !right_button_pressed && sync_button_pressed
        && !extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_sync_member);
            return;
    }

    if(left_button_pressed && right_button_pressed && !sync_button_pressed
        && !extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_stop);
            return;
    }

    if(left_button_pressed && right_button_pressed && sync_button_pressed
        && extra_button_pressed) {
            reset_buttons();
            ui_set_action(action_reboot);
            return;
    }
    reset_buttons();
}

void left_button_handler(void* arg) {
    left_button_pressed = true;

    (void) arg;
}

void right_button_handler(void* arg) {
    right_button_pressed = true;
    (void) arg;
}

void sync_button_handler(void* arg) {
    sync_button_pressed = true;
    (void) arg;
}

void extra_button_handler(void* arg) {
    extra_button_pressed = true;
    (void) arg;
}

static void reset_buttons(void) {
    left_button_pressed = false;
    right_button_pressed = false;
    sync_button_pressed = false;
    extra_button_pressed = false;
    press_detected = 0;
    return;
}

void buttons_init(void) {
    /*  init button handler */
	gpio_init_int(7,GPIO_IN,GPIO_FALLING, left_button_handler, NULL);
	gpio_init_int(8,GPIO_IN,GPIO_FALLING, right_button_handler, NULL);
	gpio_init_int(9,GPIO_IN,GPIO_FALLING, sync_button_handler, NULL);
	gpio_init_int(10,GPIO_IN,GPIO_FALLING,extra_button_handler, NULL);
    
    /* start thread for handling button events */
    thread_create(stack_buttons, sizeof(stack_buttons),
                THREAD_PRIORITY_MAIN - 1,
                THREAD_CREATE_WOUT_YIELD,
                thread_buttons,
                NULL, "thread_buttons");

}