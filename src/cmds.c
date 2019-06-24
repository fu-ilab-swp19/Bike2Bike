#include "header/cmds.h"

static bool status_checks(void);
static void set_leader(void);
static void sync_leader_completed(int argc, char** argv);

static bool status_checks(void) {
    if(_b2b_current_sent_cmd == B2B_CMD_SYNC_LEADER) {
        printf("Currently synchronizing; please stop it before doing something else!\n");
        return false;
    }
    return true;
}

int _cmd_set_id(int argc, char** argv) {
    if(argc >= 2) {
        _b2b_own_id = atoi(argv[1]);
    }
    printf("Your node id is now: %d\n", _b2b_own_id);
    return 0;
}

static void set_leader(void) {
    _b2b_user_type = B2B_TYPE_LEADER;
    return;
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
    adv_send_packet(B2B_CMD_NO_CMD, _b2b_own_id, _b2b_current_cmd_counter);
    ui_cmd_no_cmd();
    printf("Sending command: no command\n");

    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_left(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_left : You are not leader\n");
        return 0;
    }
    if(!status_checks()) {
        return 0;
    }
    
    _b2b_current_cmd_counter++;
    adv_send_packet(B2B_CMD_LEFT, _b2b_own_id, _b2b_current_cmd_counter);
    ui_cmd_left();
    (void) argc;
    (void) argv;
    return 0; 
}

int _cmd_send_right(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_LEADER) {
        printf("Not allowed command: _cmd_send_right : You are not leader\n");
        return 0;
    }
    if(!status_checks()) {
        return 0;
    }

    _b2b_current_cmd_counter++;

    adv_send_packet(B2B_CMD_RIGHT, _b2b_own_id, _b2b_current_cmd_counter);
    ui_cmd_right();
    (void) argc;
    (void) argv;
    return 0;
}

static void send_stop_leader(void) {
    _b2b_current_cmd_counter++;

    adv_send_packet(B2B_CMD_STOP, _b2b_own_id, _b2b_current_cmd_counter);
    ui_cmd_stop();
}

int _cmd_send_stop(int argc, char** argv) {
    if(!status_checks()) {
        return 0;
    }
    if(_b2b_user_type == B2B_TYPE_LEADER) {
        send_stop_leader();
    } else {
        _b2b_current_cmd_emerg_counter++;
        _b2b_current_sent_cmd_emerg = B2B_CMD_STOP;
        adv_send_packet(B2B_CMD_STOP, _b2b_own_id, _b2b_current_cmd_counter);
        ui_cmd_stop();
        printf("Sending command: Stop\n");
    }
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_sync_leader(int argc, char** argv) {
    if (_b2b_user_type == B2B_TYPE_MEMBER && _b2b_current_leader_id != -1) {
        printf("Not allowed command: _cmd_sync_leader : You are already connected to a leader\n");
        return 0;
    }
    set_leader();

    if(_b2b_current_sent_cmd == B2B_CMD_SYNC_LEADER) {
        sync_leader_completed(argc, argv);
    } else {
        _b2b_current_leader_id = _b2b_own_id;
        _b2b_current_cmd_counter++;
        adv_advertise_sync_leader(B2B_CMD_SYNC_LEADER, _b2b_own_id, _b2b_current_cmd_counter);
        ui_cmd_sync_leader();
    }
    (void) argc;
    (void) argv;
    
    return 0;
}

static void sync_leader_completed(int argc, char** argv) {
    ui_cmd_sync_leader_completed();
    _cmd_send_no_cmd(argc, argv);
}

int _cmd_sync_member(int argc, char** argv) {
    if (_b2b_user_type != B2B_TYPE_MEMBER) {
        printf("Not allowed command: _cmd_sync_member : You are not member\n");
        return 0;
    }
    adv_send_packet(B2B_CMD_SYNC_MEMBER, _b2b_own_id, _b2b_current_cmd_counter);
    ui_cmd_sync_member();
    printf("Sending command: Sync member\n");
    
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_b2b_version(int argc, char** argv) {
    (void) argc;
    (void) argv;
    printf("Bike2Bike version %s\n", B2B_VERSION);
    return 0;
}
