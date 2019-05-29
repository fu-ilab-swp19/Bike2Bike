#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"

#include "nimble_riot.h"
#include "net/bluetil/ad.h"

#include "host/ble_gap.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "services/gap/ble_svc_gap.h"

static const char *device_name = "B2B_LEAD";
static const uint8_t data[] = {0x13, 0x37, 0x13, 0x37, 0x13, 0x37};

static int gap_event_cb(struct ble_gap_event *event, void *arg)
{
    (void)arg;

    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            if (event->connect.status) {
                //start_advertise();
            }
            break;

        case BLE_GAP_EVENT_DISCONNECT:
            //start_advertise();
            break;
    }

    return 0;
}

int main(void) {
    ble_gap_adv_start
    uint8_t own_adr = BLE_OWN_ADDR_PUBLIC;
    struct ble_gap_adv_params params;
    params.conn_mode = BLE_GAP_CONN_MODE_DIR;
    params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    params.itvl_max = 0;
    params.itvl_min = 0;
    params.channel_map = 0;

    ble_svc_gap_device_name_set(device_name);
    ble_gap_adv_set_data(data, sizeof(data));
    

    printf("Start advertising...\n");
    ble_gap_adv_start(own_adr, NULL, BLE_HS_FOREVER, &params, gap_event_cb, NULL);
    xtimer_sleep(5);
    printf("Stop advertising...\n");
    return 0;
}