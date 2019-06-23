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

void ui_init(void);

void ui_cmd_changed(void);

void ui_cmd_startup(void);
void ui_cmd_left(void);
void ui_cmd_right(void); 
void ui_cmd_stop(void);
void ui_cmd_sync_member(void);
void ui_cmd_sync_member_successful(void); 
void ui_cmd_sync_leader(void);
void ui_cmd_no_cmd(void);
void ui_test(void);

#ifdef __cplusplus
}
#endif

#endif