#ifndef RECV_H 
#define RECV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nimble_scanner.h"
#include "net/bluetil/ad.h"
#include "xtimer.h"
#include "definitions.h"
#include "util.h"
#include "adv.h"
#include "crypto.h"
#include "ui.h"

typedef struct {
    uint8_t sender;
    uint8_t cmd;
    uint8_t cmd_counter;
    uint8_t cmd_emerg;
    uint8_t cmd_emerg_counter;
    uint8_t* data;
    size_t data_size;
    uint8_t aes_key[AES_KEY_SIZE];
} b2b_packet;

int recv_scan_for_new_packets(void);
void recv_init(void);

#ifdef __cplusplus
}
#endif

#endif
