#include "header/recv.h"

static int recv_check_cmd_counter(uint16_t send_cmd, uint16_t curr_cmd);

static void recv_analyze_b2b_leader_packet(uint8_t* data, size_t data_size){
    uint8_t sender = data[0+sizeof(_b2b_validation_value)];
    uint8_t cmd_counter = data[1+sizeof(_b2b_validation_value)];
    uint8_t cmd = data[2+sizeof(_b2b_validation_value)];

    if(recv_check_cmd_counter(cmd_counter, _b2b_current_cmd_counter)){
        if(_b2b_current_leader_id == -1 && _b2b_current_sent_cmd == B2B_CMD_SYNC_MEMBER) {
            if(cmd == B2B_CMD_SYNC_LEADER) {
                if(data_size >= B2B_AD_SIZE + AES_KEY_SIZE) {
                    memcpy(_b2b_aes_key, data + B2B_AD_SIZE, AES_KEY_SIZE);
                    printf("Member received new command: sync leader\n");
                    _b2b_current_leader_id = sender;
                    printf("Leader is now: B2B-Node %d\n", sender);
                    crypto_init();
                    util_print_uint8_hex(_b2b_aes_key, sizeof(_b2b_aes_key), 
                                    "Session AES128 key: ");
                    adv_advertising_stop();
                }
            }
        } else {
            if(sender == _b2b_current_leader_id){
                switch(cmd) {
                    case B2B_CMD_LEFT:
                        printf("Member received new command: left\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: left\n");
                        break;
                    case B2B_CMD_RIGHT:
                        printf("Member received new command: right\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: right\n");
                        break;
                    case B2B_CMD_STOP:
                        printf("Member received new command: stop\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: stop\n");
                        break;
                    case B2B_CMD_NO_CMD:
                        printf("Member received new command: no command\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: no command\n");
                        break;
                }
            }
        } 
    }
    

}

static void recv_analyze_b2b_member_packet(uint8_t* data, size_t data_size){
    uint8_t sender = data[0+sizeof(_b2b_validation_value)];
    uint8_t cmd_counter_emerg = data[3+sizeof(_b2b_validation_value)];
    uint8_t emerg_cmd = data[4+sizeof(_b2b_validation_value)];

    if(_b2b_user_type == B2B_TYPE_LEADER) {
        if(emerg_cmd == B2B_CMD_STOP && recv_check_cmd_counter(cmd_counter_emerg, _b2b_current_emerg_counter)){
            printf("Leader received new command: stop\n");            
        }
    }

    else{
        if(emerg_cmd == B2B_CMD_STOP && recv_check_cmd_counter(cmd_counter_emerg, _b2b_current_emerg_counter)){
            printf("Member received new command: Emergency stop\n");
            adv_advertise_packet(sender);
            printf("Sending new command: Emergency stop\n");
        }
    }

}

static void recv_analyze_b2b_packet(uint8_t* data, size_t data_size) {
    uint8_t sender = data[0+sizeof(_b2b_validation_value)];
    uint8_t cmd_counter = data[1+sizeof(_b2b_validation_value)];
    uint8_t cmd = data[2+sizeof(_b2b_validation_value)];
    uint8_t cmd_counter_emerg = data[3+sizeof(_b2b_validation_value)];
    uint8_t emerg_cmd = data[4+sizeof(_b2b_validation_value)];

    if(_b2b_user_type == B2B_TYPE_LEADER) {
        switch(cmd) {
            case B2B_CMD_STOP:
                if(recv_check_cmd_counter(cmd_counter_emerg, _b2b_current_emerg_counter)){
                    printf("Leader received new command: stop\n");
                    break;
                }
            case B2B_CMD_SYNC_MEMBER:
                break;
        }
    }

    if(_b2b_user_type == B2B_TYPE_MEMBER && recv_check_cmd_counter(cmd_counter, _b2b_current_cmd_counter)){
        if(_b2b_current_leader_id == -1 && _b2b_current_sent_cmd == B2B_CMD_SYNC_MEMBER) {
            if(cmd == B2B_CMD_SYNC_LEADER) {
                if(data_size >= B2B_AD_SIZE + AES_KEY_SIZE) {
                    memcpy(_b2b_aes_key, data + B2B_AD_SIZE, AES_KEY_SIZE);
                    printf("Member received new command: sync leader\n");
                    _b2b_current_leader_id = sender;
                    printf("Leader is now: B2B-Node %d\n", sender);
                    crypto_init();
                    util_print_uint8_hex(_b2b_aes_key, sizeof(_b2b_aes_key), 
                                    "Session AES128 key: ");
                    adv_advertising_stop();
                    set_status_green();
                }
				
				
            }
        } else {
            if(sender == _b2b_current_leader_id){
                switch(cmd) {
                    case B2B_CMD_LEFT:
                        printf("Member received new command: left\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: left\n");
                        break;
                    case B2B_CMD_RIGHT:
                        printf("Member received new command: right\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: right\n");
                        break;
                    case B2B_CMD_STOP:
                        printf("Member received new command: stop\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: stop\n");
                        break;
                    case B2B_CMD_NO_CMD:
                        printf("Member received new command: no command\n");
                        adv_advertise_packet(sender);
                        printf("Sending new command: no command\n");
                        break;
                }
            }
        } 
    }
} 

int recv_scan_for_new_packets(void) {
    nimble_scanner_start();
    xtimer_sleep(2);
    nimble_scanner_stop();
    return 0;
}


static int recv_check_cmd_counter(uint16_t send_cmd, uint16_t curr_cmd) {
	if(curr_cmd >= 240 && send_cmd >= 1 && send_cmd <= 16) {
		return 1;
	} else if(send_cmd > curr_cmd && send_cmd <= curr_cmd + 32) {
		return 1;	
	} else {
		return 0;
	}
}

static void nimble_scanner_packet_received(const ble_addr_t *addr, int8_t rssi,
                            const uint8_t *ad, size_t len) {

    assert(addr);
    assert(len <= BLE_ADV_PDU_LEN);

    (void) addr;
    (void) rssi;

    /* prepare bluetil ad */
    uint8_t tmp_ad[len];
    memcpy(tmp_ad, ad, len);

    bluetil_ad_t bluetil_ad = BLUETIL_AD_INIT(tmp_ad, len, len);
    bluetil_ad_data_t data;


    /* retrieve advertised name (has to be B2B) */
    int res = bluetil_ad_find(&bluetil_ad, BLE_GAP_AD_NAME, &data); 

    if(res == BLUETIL_AD_OK && data.len >= B2B_ADV_NAME_BASE_SIZE) {
        if(memcmp(data.data, B2B_ADV_NAME, B2B_ADV_NAME_BASE_SIZE) == 0) {

            bluetil_ad_data_t data = {0};
            res = bluetil_ad_find(&bluetil_ad, BLE_GAP_AD_SERVICE_DATA, &data);
            if(res == BLUETIL_AD_OK) {
                if(data.len >= AES_BLOCK_SIZE) {
                    /* leader id is set -> expect encrypted data*/
                    if(_b2b_current_leader_id != -1) {

                        /* decrypt received data */
                        uint8_t data_plain[AES_BLOCK_SIZE];
                        crypto_decrypt(data.data, data_plain);

                        /* check crypto validation value */
                        if(memcmp(data_plain, _b2b_validation_value, 
                            sizeof(_b2b_validation_value)) == 0) {
                            recv_analyze_b2b_packet(data_plain, sizeof(data_plain));
                        }
                    } else { 
                        
                        /* leader is not set -> expect plain data */
                        /* check crypto validation value */

                        if(memcmp(data.data, _b2b_validation_value, 
                            sizeof(_b2b_validation_value)) == 0) {
                            
                            recv_analyze_b2b_packet(data.data, data.len);
                        }
                    }
                    
                }
            }
        }
    }
}

void recv_init(void) {
        struct ble_gap_disc_params scan_params = {
        .itvl = BLE_GAP_LIM_DISC_SCAN_INT,
        .window = BLE_GAP_LIM_DISC_SCAN_WINDOW,
        .filter_policy = 0,                         
        .limited = 0,                               
        .passive = 0,                               
        . filter_duplicates = 1,                    
    };  
    
    nimble_scanner_init(&scan_params, nimble_scanner_packet_received);
}
