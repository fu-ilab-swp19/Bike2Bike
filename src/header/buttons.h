#ifndef BUTTONS_H
#define BUTTONS_H

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

#include "cmds.h"
#include "gpio_config.h"

#define BUTTONS_THREAD_SLEEP_MS                 (250000)

void buttons_init(void);

#ifdef __cplusplus
}
#endif

#endif