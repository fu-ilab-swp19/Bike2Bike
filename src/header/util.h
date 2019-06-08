#ifndef UTIL_H 
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

size_t util_get_own_id_length(void);
void util_print_b2b_packet(uint8_t* data);
void util_print_uint8_hex(uint8_t* data, size_t size, char* output);

#ifdef __cplusplus
}
#endif

#endif
