#ifndef LEDS_H
#define LEDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "periph/gpio.h"
#include "periph_conf.h"
#include "xtimer.h"
#include "mutex.h"

#include "gpio_config.h"

/* don't change value! */
#define LEDS_PER_EVENT                          (6)
#define LEDS_ELAPSING_TIME_MS                   (500)   
#define LEDS_SLEEP_NONE_EVENT_MS                (500)

#define LEDS_CMD_LEFT_DURATION_MS               (15000)
#define LEDS_CMD_RIGHT_DURATION_MS              (15000)

enum led_event_type { none, flash, flash_endless, blink_color, blink};

typedef struct {
    enum led_event_type event_type;
    uint8_t leds[LEDS_PER_EVENT];
    uint8_t leds_count;
    int32_t event_time_ms;
} led_event;  

void leds_init(void);
void leds_new_event(led_event* evt, led_event* evt_succ); 
void leds_event_stop(void);
void leds_set_status_green(void);
void leds_set_status_red(void);
void leds_reset_status(void);

#ifdef __cplusplus
}
#endif

#endif