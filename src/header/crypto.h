#ifndef CRYPTO_H 
#define CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include "shell_commands.h"
#include "definitions.h"
#include "crypto/ciphers.h"

#include "net/bluetil/ad.h"

void crypto_init(void);
void crypto_encrypt(uint8_t* plain_data, uint8_t* cipher_data);
void crypto_decrypt(uint8_t* cipher_data, uint8_t* plain_data);


#ifdef __cplusplus
}
#endif

#endif
