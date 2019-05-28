#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "periph/gpio.h"
#include "periph_conf.h"

#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"

#define FLANK      GPIO_FALLING
#define DELAY_SHORT (500000UL)

void cb_btn0(void *arg)
{
    printf("Links abbiegen!\n");
    (void) arg;
}

void cb_btn1(void *arg) {
    printf("Rechts abbiegen!\n");
    (void) arg;
}

void cb_btn2(void *arg) {
    printf("Stopp!\n");
    (void) arg;
}

void cb_btn3(void *arg) {
    printf("Langsamer!\n");
    (void) arg;
}

void delay(uint32_t delay) {
    xtimer_usleep(delay);
}

int LED_TEST(void) {
    for(int i = 0; i < 5; i++) {
        LED0_ON;
        delay(DELAY_SHORT);
        LED1_ON;
        delay(DELAY_SHORT);
        LED2_ON;
        delay(DELAY_SHORT);
        LED3_ON;
        delay(DELAY_SHORT);
        LED0_OFF;
        delay(DELAY_SHORT);
        LED1_OFF;
        delay(DELAY_SHORT);
        LED2_OFF;
        delay(DELAY_SHORT);
        LED3_OFF;
        delay(DELAY_SHORT);
    }
    return 0;
}

int BTN_INIT(void) {
    int count = 0;
    gpio_init_int(BTN0_PIN, BTN0_MODE, FLANK, cb_btn0, (void *)count);
    count++;
    gpio_init_int(BTN1_PIN, BTN1_MODE, FLANK, cb_btn1, (void *)count);
    count++;
    gpio_init_int(BTN2_PIN, BTN3_MODE, FLANK, cb_btn2, (void *)count);
    count++;
    gpio_init_int(BTN3_PIN, BTN3_MODE, FLANK, cb_btn3, (void *)count);

    return 0;
}

int main(void) {
    BTN_INIT();
    LED_TEST();
    return 0;
}


