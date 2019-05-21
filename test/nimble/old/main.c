#include <string.h>
#include "shell.h"
#include "thread.h"
#include "xtimer.h"
#include "nrfble.h"
#include "RIOT/drivers/include/net/netdev/ble.h"
#include "net/eui64.h"


int bluetooth_start(int argc, char** argv);
int timer_stuff(int argc, char **argv);
int bluetooth_print_settings(int argc, char **argv);
void event_1(netdev_t* netdev, netdev_event_t event);

char stack[THREAD_STACKSIZE_MAIN];

static const shell_command_t commands[] = {
    { "timer_stuff", "Timer Test", timer_stuff},
    { "b", "Start bluetooth", bluetooth_start},
    { "s", "Print bluetooth settings", bluetooth_print_settings},
    { NULL, NULL, NULL }
};

netdev_t netdev;

int main(void)
{
    puts("This board is running Bike2Bike");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

void* bluetooth_thread(void* arg) {
    netdev = *nrfble_setup();
    printf("Trying init...\n");
    netdev.event_callback = event_1;
    //netdev.driver->init(&netdev);
    printf("Dinge sind passiert\n");
    netdev_ble_pkt_t pkt;
    //memset(pkt.pdu, 0x020106110707b9f9d750a420897740cbfd2cc18048090842474d3131312053, sizeof(pkt.pdu));
    while(true) {
        printf("Listening...\n");
        netdev_ble_send(&netdev, &pkt);
        //xtimer_sleep(1);
    }
    (void)arg;
    return NULL;
}

void event_1(netdev_t* netdev, netdev_event_t event) {
    printf("Ey yo event!\n");
    (void) netdev;
    (void) event;
}


int bluetooth_print_settings(int argc, char **argv) {
    uint16_t device_type;
    uint16_t device_state;
    uint8_t address[2];

    netdev.driver->get(&netdev, NETOPT_DEVICE_TYPE, (void*)&device_type, sizeof(uint16_t));
    netdev.driver->get(&netdev, NETOPT_STATE, (void*)&device_state, sizeof(uint16_t));
    netdev.driver->get(&netdev, NETOPT_ADDRESS, (void*)&address, sizeof(address));
    printf("DEVICE_TYPE: %i\n", device_type);
    printf("ADDRESS: %i%i\n", address[0], address[1]);
    switch(device_state) {
        case(0):
            printf("NETOPT_STATE: OFF\n");
            break;
        case(1):
            printf("NETOPT_STATE: SLEEP\n");
            break;
        case(2):
            printf("NETOPT_STATE: IDLE\n");
            break;
        case(3):
            printf("NETOPT_STATE: RX\n");
            break;
        case(4):
            printf("NETOPT_STATE: TX\n");
            break;
        case(5):
            printf("NETOPT_STATE: RESET\n");
            break;
        case(6):
            printf("NETOPT_STATE: STANDBY\n");
            break;
        default:
            printf("NETOPT_STATE: UNKNOWN: %i\n", device_state);
            break;
    }
    (void) argc;
    (void) argv;
    return 0;
}

int bluetooth_start(int argc, char** argv) {
    thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN-1, THREAD_CREATE_STACKTEST, bluetooth_thread, NULL, "bluetooth-thread");
    (void) argc;
    (void)argv;
    return 0;
}

void* timer_thread(void* arg) {
    for(int i = 0; i < 10; i++) {
        printf("Current time: %ld s\n", xtimer_now_usec()/1000000);
        xtimer_sleep(2);
    }
    (void) arg;
    return NULL;
}

int timer_stuff(int argc, char** argv) {
    thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN-1, THREAD_CREATE_STACKTEST, timer_thread, NULL, "timer-thread");
    (void) argc;
    (void) argv;
    return 0;
}


