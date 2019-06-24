#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "leds.h"
#include "buttons.h"
#include "mutex.h"

enum action { action_none, action_left, action_right, action_stop, action_sync_leader, 
                action_sync_member, action_reboot };


void ui_init(void);

void ui_cmd_changed(void);

void ui_cmd_startup(void);
void ui_cmd_left(void);
void ui_cmd_right(void); 
void ui_cmd_stop(void);
void ui_cmd_sync_member(void);
void ui_cmd_sync_member_successful(void); 
void ui_cmd_sync_leader(void);
void ui_cmd_sync_leader_completed(void);
void ui_cmd_no_cmd(void);
void ui_set_action(enum action new_action);
enum action ui_get_action(void);

#ifdef __cplusplus
}
#endif

#endif