#include "header/leds.h"

static void event_flash(void);
static void event_flash_endless(void);
static void event_blink(void); 
static void event_blink_color(void);
static void event_activate_next_event(void);

char stack_leds[THREAD_STACKSIZE_SMALL];

mutex_t mutex_event;
led_event event = {none};
led_event event_succ = {none};

static void* thread_leds(void* arg) {
    (void) arg;
    bool sleep;

    while(true) {
        sleep = false;

        if(event.event_type != none) {
            mutex_lock(&mutex_event);

            if(event.event_time_ms <= 0) {
                if(event.event_type != flash_endless) {
                    leds_event_stop();
                } else {
                    event.event_type = none;
                } 

                if(event_succ.event_type != none) {
                    event_activate_next_event();
                }
            } else {
                switch (event.event_type)
                {
                    case flash:
                        event_flash();
                        break;
                    case flash_endless:
                        event_flash_endless();
                        break;
                    case blink:
                        event_blink();
                        break;
                    case blink_color:
                        event_blink_color();
                        break;
                    default:
                        break;
                }
                event.event_time_ms -= LEDS_ELAPSING_TIME_MS;
                sleep = true; 

            }
            mutex_unlock(&mutex_event);
            if(sleep == 1) {
                xtimer_usleep(LEDS_ELAPSING_TIME_MS * 1000);
            }
        } else {
            xtimer_usleep(LEDS_SLEEP_NONE_EVENT_MS * 1000);
        }
    }
    return NULL;
}

static void event_flash_endless(void) {
    /* set leds on */
    for(uint8_t i = 0; i < event.leds_count; i++) {
        gpio_write(event.leds[i], 1);
   }
}
static void event_flash(void) {
    /* set leds on */
    for(uint8_t i = 0; i < event.leds_count; i++) {
        gpio_write(event.leds[i], 1);
   }
}

static void event_blink(void) {
    if(event.leds_count > 1) {
        for(uint8_t i = 0; i < event.leds_count; i++) {
            gpio_toggle(event.leds[i]);
        }
    }
}

static void event_blink_color(void) {
    for(uint8_t i = 0; i < event.leds_count; i += 2) {
        uint8_t led1, led2;
        led1 = gpio_read(event.leds[i]);
        led2 = gpio_read(event.leds[i+1]);
        if(led1 == 0 && led2 == 0) {
            led1 = 1;
        }

        gpio_write(event.leds[i], led2);
        gpio_write(event.leds[i+1], led1);
    }
}

static bool event_validation(led_event* evt) {
    switch(evt->event_type) {
        case none:
            break;
        case blink:
            if(evt->leds_count == 0) {
                return false;
            }
            break;
        case blink_color:
            if(evt->leds_count%2 != 0) {
                return false;
            }
            break;
        case flash:
            if(evt->leds_count == 0) {
                return false;
            }
            break;
        case flash_endless:
            if(evt->leds_count == 0) {
                return false;
            }
            break;
    }

    if(evt->event_time_ms <= 0) {
        return false;
    }

    return true;
}

void leds_event_stop(void) {
    if(event.event_type != none) {
        event.event_type = none;
        for(uint8_t i = 0; i < event.leds_count; i++) {
                gpio_write(event.leds[i], 0);
        }
    }
}

void leds_new_event(led_event* evt, led_event* evt_succ) {
    if(event_validation(evt)) {
        mutex_lock(&mutex_event);
        leds_event_stop();
        memcpy(&event, evt, sizeof(event));
        
        if(evt_succ != NULL) {
            memcpy(&event_succ, evt_succ, sizeof(event_succ));
        }

        mutex_unlock(&mutex_event);
    } else
    {
        printf("LED event error: Event is invalid!\n");
    }
    
}

static void event_activate_next_event(void) {
    memcpy(&event, &event_succ, sizeof(event));
    event_succ.event_type = none;
}

void leds_set_status_green(void) {
    gpio_write(LED_STATUS_GREEN, 1);
}

void leds_set_status_red(void) {
    gpio_write(LED_STATUS_RED, 1);
}

void leds_reset_status(void) {
    gpio_write(LED_STATUS_GREEN, 0);
    gpio_write(LED_STATUS_RED, 0);
}

void leds_init(void) {
    /* Init output Pins */
    gpio_init(LED_STATUS_GREEN,GPIO_OUT);  /* status green */
    gpio_init(LED_STATUS_RED,GPIO_OUT); /* status red */

    gpio_init(LED_LEFT_GREEN,GPIO_OUT); /* left green */
    gpio_init(LED_LEFT_RED,GPIO_OUT); /* left red */
	
    gpio_init(LED_RIGHT_GREEN,GPIO_OUT);  /* right green */
    gpio_init(LED_RIGHT_RED,GPIO_OUT); /* right red */
	
	/* set all leds to off */
	gpio_write(LED_STATUS_GREEN,0);
	gpio_write(LED_STATUS_RED,0);
	gpio_write(LED_LEFT_GREEN,0);
	gpio_write(LED_LEFT_RED,0);
	gpio_write(LED_RIGHT_GREEN,0);
	gpio_write(LED_RIGHT_RED,0);

    mutex_init(&mutex_event);

    event.event_type = none;
    event.event_time_ms = 0;

    thread_create(stack_leds, sizeof(stack_leds),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_WOUT_YIELD,
                    thread_leds,
                    NULL, "thread_leds");
}