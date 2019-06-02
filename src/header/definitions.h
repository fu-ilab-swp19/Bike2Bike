#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


#define B2B_TYPE_NONE               (0x0)
#define B2B_TYPE_MEMBER             (0x1)
#define B2B_TYPE_LEADER             (0x2)

#define B2B_CMD_SYNC_LEADER         (0x00)
#define B2B_CMD_SYNC_MEMBER         (0x01)

#define B2B_CMD_LEFT                (0x02)
#define B2B_CMD_RIGHT               (0x03)
#define B2B_CMD_STOP                (0x04)
#define B2B_CMD_NO_CMD              (0x05)

#define B2B_AD_RECOGNITION_ID_SIZE  (4)
#define B2B_AD_SIZE                 (3)

extern const char   B2B_ADV_NAME[10];
extern const uint8_t B2B_RECONGITION_ID[B2B_AD_RECOGNITION_ID_SIZE];

extern uint8_t       _b2b_own_id;
extern uint8_t       _b2b_cmd_counter;
extern uint8_t       _b2b_user_type;

#ifdef __cplusplus
}
#endif

#endif