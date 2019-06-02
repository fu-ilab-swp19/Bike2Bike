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

int adv_advertise_packet(uint8_t cmd, uint8_t sender_id, uint8_t cmd_counter);

#ifdef __cplusplus
}
#endif

#endif
