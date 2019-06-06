#include "header/recv.h"

void recv_init(void) {
        struct ble_gap_disc_params scan_params = {
        .itvl = BLE_GAP_LIM_DISC_SCAN_INT,
        .window = BLE_GAP_LIM_DISC_SCAN_WINDOW,
        .filter_policy = 0,                         
        .limited = 0,                               
        .passive = 0,                               
        . filter_duplicates = 0,                    
    };  
    
    nimble_scanlist_init();
    nimble_scanner_init(&scan_params, nimble_scanlist_update);
}

int recv_scan_for_new_packets(void) {
    //printf("Start scanning environment\n");
    nimble_scanlist_clear();

    nimble_scanner_start();
    xtimer_sleep(2);
    nimble_scanner_stop();

    nimble_scanlist_entry_t* e = NULL;

    e = nimble_scanlist_get_next(e);
    //printf("----------------------\n");
    while(e) {
        bluetil_ad_t ad = BLUETIL_AD_INIT(e->ad, e->ad_len, e->ad_len);
        bluetil_ad_data_t data;
        int res = bluetil_ad_find(&ad, BLE_GAP_AD_NAME, &data);  
        if(res == BLUETIL_AD_OK && data.len >= B2B_ADV_NAME_BASE_SIZE) {
            if(memcmp(data.data, B2B_ADV_NAME, B2B_ADV_NAME_BASE_SIZE) == 0) {
                res = bluetil_ad_find(&ad, BLE_GAP_AD_SERVICE_DATA, &data);
                if(res == BLUETIL_AD_OK) {
                    recv_analyze_b2b_packet(data.data);
                }
            }
        }
        e = nimble_scanlist_get_next(e);
    }   
    return 0;
}

void recv_analyze_b2b_packet(uint8_t* data) {
    uint8_t sender = data[0];
    uint8_t cmd_counter = data[1];
    uint8_t cmd = data[2];

    if(_b2b_user_type == B2B_TYPE_LEADER) {
        switch(cmd) {
            case B2B_CMD_STOP:
                printf("Leader received new command: stop\n");
                break;
            case B2B_CMD_SYNC_MEMBER:
                printf("Leader received command: sync member\n");
                break;
        }
    }

    if(_b2b_user_type == B2B_TYPE_MEMBER && cmd_counter > _b2b_current_cmd_counter) {
        if(_b2b_current_leader_id == -1 && _b2b_current_sent_cmd == B2B_CMD_SYNC_MEMBER) {
            if(cmd == B2B_CMD_SYNC_LEADER) {
                printf("Member received new command: sync leader\n");
                _b2b_current_leader_id = sender;
                printf("Leader is now: B2B-Node %d\n", sender);
            }
        } else {
            if(sender == _b2b_current_leader_id){
                switch(cmd) {
                    case B2B_CMD_LEFT:
                        printf("Member received new command: left\n");
                        adv_advertise_packet(cmd, sender, cmd_counter);
                        printf("Sending new command: left\n");
                        break;
                    case B2B_CMD_RIGHT:
                        printf("Member received new command: right\n");
                        adv_advertise_packet(cmd, sender, cmd_counter);
                        printf("Sending new command: right\n");
                        break;
                    case B2B_CMD_STOP:
                        printf("Member received new command: stop\n");
                        adv_advertise_packet(cmd, sender, cmd_counter);
                        printf("Sending new command: stop\n");
                        break;
                    case B2B_CMD_NO_CMD:
                        printf("Member received new command: no command\n");
                        adv_advertise_packet(cmd, sender, cmd_counter);
                        printf("Sending new command: no command\n");
                        break;
                }
            }
        } 
    }

    (void) cmd_counter;

} 