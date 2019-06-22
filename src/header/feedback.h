#ifndef FEEDBACK_H
#define FEEDBACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

void feedback_cmd_changed(void);

void feedback_cmd_left(void);
void feedback_cmd_right(void); 
void feedback_cmd_stop(void);
void feedback_cmd_sync_member(void);
void feedback_cmd_sync_member_successful(void); 
void feedback_cmd_sync_leader(void);
void feedback_cmd_no_cmd(void);

#ifdef __cplusplus
}
#endif

#endif