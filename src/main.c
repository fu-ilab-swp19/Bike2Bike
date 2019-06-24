#include "header/cmds.h"
#include "header/recv.h"
#include "header/adv.h"
#include "header/crypto.h"
#include "header/ui.h"

static void check_for_new_actions(void);
static void* thread_program(void* arg);
static void init(void);

uint8_t _b2b_validation_value[] = { 0xAC, 0xDC };
const char   B2B_ADV_NAME[] = "B2B";

uint8_t _b2b_user_type;
uint8_t _b2b_own_id;
uint8_t _b2b_current_cmd_sender;
uint8_t _b2b_current_cmd_counter;
uint8_t _b2b_current_cmd_emerg_counter;
int8_t _b2b_current_leader_id;
int8_t _b2b_current_sent_cmd;
int8_t _b2b_current_sent_cmd_emerg;

char stack[THREAD_STACKSIZE_DEFAULT];


int main(void) {
    init();
    printf("Bike2Bike version %s\n", B2B_VERSION);

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

static void init(void) {
	ui_init();
    crypto_init();
    recv_init();

    _b2b_user_type = B2B_TYPE_MEMBER;
    _b2b_own_id = 1;
    _b2b_current_leader_id = -1;
    _b2b_current_cmd_sender = -1;
    _b2b_current_sent_cmd = B2B_CMD_NONE;
    _b2b_current_sent_cmd_emerg = B2B_CMD_NONE;
    _b2b_current_cmd_counter = 0;
    _b2b_current_cmd_emerg_counter = 0;
    printf("Init completed\n");
    ui_cmd_startup();
}

static void* thread_program(void* arg) {
    while(true) {
        check_for_new_actions();
        recv_scan_for_new_packets();
        xtimer_usleep(300000);
    }
    (void) arg;
    return NULL;
}

static void check_for_new_actions(void) {
    enum action ctx = ui_get_action();
    switch(ctx) {
        case action_none:
            break;
        case action_left:
            _cmd_send_left(0, NULL);
            break;
        case action_right:
            _cmd_send_right(0, NULL);
            break;
        case action_stop:
            _cmd_send_stop(0, NULL);
            break;
        case action_sync_leader:
            _cmd_sync_leader(0, NULL);
            break;
        case action_sync_member:
            _cmd_sync_member(0, NULL);
            break;
        case action_reboot:
            /* there has to be a clean way to reboot the board?! */
            printf("Let it crash, let it crash, let it crash: %d\n", *(&ctx-10000));
            break;
    }
}

