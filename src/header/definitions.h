#ifndef DEFINITIONS_H 
#define DEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

extern uint8_t       _cmd_counter;
extern uint8_t       _user_type;

#define _own_id =         {0x01};

#define B2B_TYPE_USER           (0x0)
#define B2B_TYPE_LEADEr         (0x1)

#define B2B_CMD_SYNC_LEADER     (0x00)
#define B2B_CMD_SYNC_MEMBER     (0x01)

#define B2B_CMD_LEFT            (0x02)
#define B2B_CMD_RIGHT           (0x03)
#define B2B_CMD_STOP            (0x04)
#define B2B_CMD_NO_CMD          (0x05)

#ifdef __cplusplus
}
#endif

#endif