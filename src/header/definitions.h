#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "crypto/ciphers.h"

#define AES_KEY_SIZE                (16)
#define AES_BLOCK_SIZE              (16)

#define B2B_TYPE_NONE               (0x0)
#define B2B_TYPE_MEMBER             (0x1)
#define B2B_TYPE_LEADER             (0x2)

#define B2B_CMD_SYNC_LEADER         (0x00)
#define B2B_CMD_SYNC_MEMBER         (0x01)

#define B2B_CMD_LEFT                (0x02)
#define B2B_CMD_RIGHT               (0x03)
#define B2B_CMD_STOP                (0x04)
#define B2B_CMD_NO_CMD              (0x05)

#define B2B_AD_SIZE                 (0x03)


extern cipher_t      _b2b_cipher;
extern uint8_t       _b2b_aes_key[AES_KEY_SIZE];

extern uint8_t       _b2b_own_id;
extern uint8_t       _b2b_user_type;
extern int8_t        _b2b_current_leader_id;
extern int8_t        _b2b_current_sent_cmd;
extern uint8_t       _b2b_current_cmd_counter;

#ifdef __cplusplus
}
#endif

#endif