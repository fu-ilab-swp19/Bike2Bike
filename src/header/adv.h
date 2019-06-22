#ifndef ADV_H 
#define ADV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nimble_riot.h"
#include "net/bluetil/ad.h"
#include "host/ble_hs.h"
#include "host/util/util.h"

#include "util.h"
#include "definitions.h"
#include "crypto.h"


void adv_send_packet(uint8_t cmd, uint8_t sender_id, uint8_t cmd_counter);

void adv_advertise_sync_leader(uint8_t cmd, uint8_t sender_id, 
    uint8_t cmd_counter);
void adv_advertise_start(void);
void adv_advertising_stop(void);

#ifdef __cplusplus
}
#endif

#endif
