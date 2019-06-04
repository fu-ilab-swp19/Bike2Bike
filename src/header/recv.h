#ifndef RECV_H 
#define RECV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nimble_scanner.h"
#include "nimble_scanlist.h"
#include "net/bluetil/ad.h"
#include "xtimer.h"
#include "definitions.h"
#include "util.h"
#include "adv.h"

int recv_scan_for_new_packets(void);
void recv_init(void);
void recv_analyze_b2b_packet(uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif