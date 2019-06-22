#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "crypto/ciphers.h"

#define AES_KEY_SIZE                (16U)
#define AES_BLOCK_SIZE              (16U)

#define B2B_VERSION                 "0.7"
#define B2B_TYPE_NONE               (0x00)
#define B2B_TYPE_MEMBER             (0x01)
#define B2B_TYPE_LEADER             (0x02)

#define B2B_CMD_SYNC_LEADER         (0x00)
#define B2B_CMD_SYNC_MEMBER         (0x01)

#define B2B_CMD_LEFT                (0x02)
#define B2B_CMD_RIGHT               (0x03)
#define B2B_CMD_STOP                (0x04)
#define B2B_CMD_NO_CMD              (0x05)
#define B2B_CMD_NONE                (0x06)

#define B2B_AD_SIZE                 (0x07)
#define B2B_AD_AES_POS              (0x05)
#define B2B_ADV_NAME_BASE_SIZE      (0x03)

extern const char   B2B_ADV_NAME[4];

extern cipher_t     _b2b_cipher;
extern uint8_t      _b2b_aes_key[AES_KEY_SIZE];

extern uint8_t      _b2b_own_id;
extern uint8_t      _b2b_user_type;
extern int8_t       _b2b_current_leader_id;
extern uint8_t      _b2b_current_cmd_sender;
extern int8_t       _b2b_current_sent_cmd;
extern int8_t       _b2b_current_sent_cmd_emerg;
extern uint8_t      _b2b_current_cmd_emerg_counter;
extern uint8_t      _b2b_current_cmd_counter;
extern uint8_t      _b2b_validation_value[2];

#ifdef __cplusplus
}
#endif

#endif