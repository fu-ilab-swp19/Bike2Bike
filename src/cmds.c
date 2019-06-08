#include "header/cmds.h"

int _cmd_set_id(int argc, char** argv) {
    if(argc >= 2) {
        _b2b_own_id = atoi(argv[1]);
    }
    printf("Your node id is now: %d\n", _b2b_own_id);
    return 0;
}

int _cmd_set_leader(int argc, char** argv) {
    _b2b_user_type = B2B_TYPE_LEADER;
    printf("You are leader now!\n");
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_set_cmd_counter(int argc, char** argv) {
    if(argc >= 2) {
        _b2b_current_cmd_counter = atoi(argv[1]);
    }
    printf("Command counter is now: %d", _b2b_current_cmd_counter);
    return 0;
}

int _cmd_send_no_cmd(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_no_cmd : You are not leader\n");
        return 0;
    }
    _b2b_current_cmd_counter++;
    adv_advertise_packet(B2B_CMD_NO_CMD, _b2b_own_id, _b2b_current_cmd_counter);
    printf("Sending command: Right\n");

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_left(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_left : You are not leader\n");
        return 0;
    }
    
    _b2b_current_cmd_counter++;
	signal_left_red();
    adv_advertise_packet(B2B_CMD_LEFT, _b2b_own_id, _b2b_current_cmd_counter);
	

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
    _b2b_current_cmd_counter++;
	signal_right_red();
    adv_advertise_packet(B2B_CMD_RIGHT, _b2b_own_id, _b2b_current_cmd_counter);
    printf("Sending command: Right\n");

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_stop(int argc, char** argv) {
    _b2b_current_cmd_counter += 10;
    adv_advertise_packet(B2B_CMD_STOP, _b2b_own_id, _b2b_current_cmd_counter);
    printf("Sending command: Stop\n");
    
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_sync_leader(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_sync_leader : You are not leader\n");
        return 0;
    }
    _b2b_current_leader_id = _b2b_own_id;
    _b2b_current_cmd_counter++;
    adv_advertise_packet(B2B_CMD_SYNC_LEADER, _b2b_own_id, _b2b_current_cmd_counter);
    printf("Sending command: Sync lead\n");
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_sync_member(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_MEMBER) {
        printf("Not allowed command: _cmd_sync_member : You are not member\n");
        return 0;
    }
    adv_advertise_packet(B2B_CMD_SYNC_MEMBER, _b2b_own_id, _b2b_current_cmd_counter);
    printf("Sending command: Sync member\n");
    (void) argc;
    (void) argv;
    return 0;
}
