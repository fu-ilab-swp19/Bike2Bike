
    if(argc >= 2) {
        _b2b_own_id = atoi(argv[1]);
    }
    printf("Your node id is now: %d\n", _b2b_own_id);
    return 0;
}

int _cmd_set_leader(int argc, char** argv) {
    _b2b_user_type = B2B_TYPE_LEADER;
    printf("You are leader now!\n");
	set_status_red();
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
    _b2b_current_sent_cmd = B2B_CMD_NONE;
    adv_advertise_packet(_b2b_own_id);
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
    _b2b_current_sent_cmd = B2B_CMD_LEFT;
    adv_advertise_packet(_b2b_own_id);


    printf("Sending command: Left\n");
			signal_left_red();
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
    _b2b_current_sent_cmd = B2B_CMD_RIGHT;
    adv_advertise_packet(_b2b_own_id);
    printf("Sending command: Right\n");
	signal_right_red();
    (void) argc;
    (void) argv;
    return 0;
}

int _cmd_send_stop(int argc, char** argv) {
    if(_b2b_user_type != B2B_TYPE_LEADER){
        _b2b_current_emerg_counter++;
        _b2b_current_emerg_cmd = B2B_CMD_STOP;
        adv_advertise_packet(_b2b_own_id);
        printf("Sending command: Emergency stop\n");

        (void) argc;
        (void) argv;
        return 0;
    }    
    _b2b_current_cmd_counter++;
    _b2b_current_sent_cmd = B2B_CMD_STOP;
    adv_advertise_packet(_b2b_own_id);
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
    _b2b_current_sent_cmd = B2B_CMD_SYNC_LEADER;
    adv_advertise_packet(_b2b_own_id);
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
    _b2b_current_sent_cmd = B2B_CMD_SYNC_MEMBER;
    adv_advertise_packet(_b2b_own_id);
    printf("Sending command: Sync member\n");
    (void) argc;
    (void) argv;
    return 0;
}
