#include "header/cmds.h"

int _cmd_test_adv(int argc, char** argv) {
    printf("Test advertising...\n");
    
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_test_recv(int argc, char** argv) {
    printf("Test receiving...\n");

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_set_id(int argc, char** argv) {
    if(argc >= 2) {
        _b2b_own_id = atoi(argv[1]);
    }
    printf("Your node id is now: %d\n", _b2b_own_id);
    return 0;
}

int _cmd_send_no_cmd(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_no_cmd : You are not leader\n");
        return 0;
    }

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_left(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_left : You are not leader\n");
        return 0;
    }

    printf("Sending command: Left\n");
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_right(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_right : You are not leader\n");
        return 0;
    }

    printf("Sending command: Right\n");
    
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_stop(int argc, char** argv) {

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_sync_lead(int argc, char** argv) {
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_sync_member(int argc, char** argv) {
    (void) argc;
    (void) argv;
    return 0;
}