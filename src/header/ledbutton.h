#ifndef LEDBUTTON_H 
#define LEDBUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "cmds.h"

#include "board.h"
#include "periph/gpio.h"
#include "periph_conf.h"
#include "xtimer.h"


void signal_left_green(void);
void signal_right_green(void);


void signal_left_red(void);
void signal_right_red(void);

void signal_status_green(void);
void signal_status_red(void);
void led_init(void);

void set_status_red(void);
void set_status_green(void);
void reset_status(void);

#ifdef __cplusplus
}
#endif

#endif
