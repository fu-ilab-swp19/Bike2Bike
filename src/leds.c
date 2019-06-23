#include "header/leds.h"

static void event_flash(void);
static void event_blink(void); 
static void event_blink_color(void);

char stack_leds[THREAD_STACKSIZE_SMALL];

mutex_t mutex_event;
led_event event = {none};

static void* thread_leds(void* arg) {
    (void) arg;
    bool sleep;

    while(true) {
        sleep = false;

        if(event.event_type != none) {
            mutex_lock(&mutex_event);

            if(event.event_time_ms <= 0) {
                printf("EVENT RESET\n");
                leds_event_stop();
            } else {
                switch (event.event_type)
                {
                    case flash:
                        event_flash();
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

static void event_flash(void) {
    /* set leds on */
    for(uint8_t i = 0; i < event.leds_count; i++) {
        gpio_write(event.leds[i], 1);
   }
}

static void event_blink(void) {
    if(event.leds_count == 1) {
        gpio_toggle(event.leds[0]);
    }

    if(event.leds_count > 1) {
        for(uint8_t i = 0; i < event.leds_count; i++) {
            gpio_toggle(event.leds[i]);
        }
    }
}

static void event_blink_color(void) {
    if(event.leds_count == 2) {
        uint8_t led1, led2;
        led1 = gpio_read(event.leds[0]);
        led2 = gpio_read(event.leds[1]);
        if(led1 == 0 && led2 == 0) {
            led1 = 1;
        }

        gpio_write(event.leds[0], led2);
        gpio_write(event.leds[1], led1);
    }
}

void leds_event_stop(void) {
    if(event.event_type != none) {
        event.event_type = none;
        for(uint8_t i = 0; i < event.leds_count; i++) {
                gpio_write(event.leds[i], 0);
        }
    }
}

void leds_new_event(led_event* led_evt) {
    mutex_lock(&mutex_event);
    leds_event_stop();
    memcpy(&event, led_evt, sizeof(event));
    mutex_unlock(&mutex_event);
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