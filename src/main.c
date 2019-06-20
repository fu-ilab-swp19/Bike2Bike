#include "header/cmds.h"
#include "header/recv.h"
#include "header/adv.h"
#include "header/crypto.h"
#include "header/ledbutton.h"

uint8_t _b2b_validation_value[] = { 0xAC, 0xDC };
const char   B2B_ADV_NAME[] = "B2B";

uint8_t _b2b_user_type;
uint8_t _b2b_own_id;

uint8_t _b2b_current_cmd_counter;
int8_t _b2b_current_leader_id;
int8_t _b2b_current_sent_cmd;

char stack[THREAD_STACKSIZE_DEFAULT];

static void init(void) {
    _b2b_user_type = B2B_TYPE_MEMBER;
    _b2b_own_id = 1;
    _b2b_current_leader_id = -1;
    _b2b_current_sent_cmd = -1;
    _b2b_current_cmd_counter = 0;
    
	led_init();
    crypto_init();
    recv_init();
}

void* thread_program(void* arg) {
    while(true) {
        recv_scan_for_new_packets();
        xtimer_sleep(2);
    }
    (void) arg;
    return NULL;
}

int main(void) {
    init();

    puts("Init completed\n");
    puts("Bike2Bike program started");

    thread_create(stack, sizeof(stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_program,
                    NULL, "thread");

    /* run shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
