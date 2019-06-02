#ifndef CMDS_H 
#define CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"
#include "definitions.h"

int _cmd_test_adv(int argc, char** argv);
int _cmd_test_recv(int argc, char** argv);

int _cmd_send_left(int argc, char** argv);
int _cmd_send_right(int argc, char** argv);
int _cmd_send_stop(int argc, char** argv);

int _cmd_sync_lead(int argc, char** argv);
int _cmd_sync_member(int argc, char** argv);

static const shell_command_t _commands[] = {
    { "test_adv", "make a test advertising", _cmd_test_adv },
    { "test_recv", "receive ble data and print it out", _cmd_test_recv},
    { "send_left", "(lead) send signal to others: left", _cmd_send_left},
    { "send_right", "(lead) send signal to others: right", _cmd_send_right},
    { "send_stop", "(member) send signal to leader: stop", _cmd_send_stop},
    { "sync_lead", "(lead) initiate leader sync", _cmd_sync_lead},
    { "sync_member", "(member) initiate member sync", _cmd_sync_member},
    { NULL, NULL, NULL }
};

#ifdef __cplusplus
}
#endif

#endif
