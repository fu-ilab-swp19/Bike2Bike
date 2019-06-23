#include "header/recv.h"

static int check_cmd_counter(uint16_t send_cmd, uint16_t curr_cmd);
static void prepare_b2b_packet(b2b_packet* packet, uint8_t* data, uint8_t len);

static void process_b2b_packet_leader(b2b_packet* packet);
static void process_b2b_packet_member(b2b_packet* packet);


static void process_b2b_packet_leader(b2b_packet* packet) {
    if(check_cmd_counter(packet->cmd_emerg_counter, _b2b_current_cmd_emerg_counter)) {
        if(packet->cmd_emerg == B2B_CMD_STOP) {
            _b2b_current_sent_cmd_emerg = B2B_CMD_NONE;
            _b2b_current_cmd_emerg_counter = packet->cmd_emerg_counter+1;
            ui_cmd_stop();
            adv_advertise_start();
        }
    }
}

static void process_b2b_packet_member(b2b_packet* packet) {
    /* no leader, device is looking for leader */    
    if(_b2b_current_leader_id == -1 && _b2b_current_sent_cmd == B2B_CMD_SYNC_MEMBER) {
        if(packet->cmd == B2B_CMD_SYNC_LEADER) {
            memcpy(_b2b_aes_key, packet->aes_key, AES_KEY_SIZE);
            printf("Member received new command: sync leader\n");

            _b2b_current_leader_id = packet->sender;
            printf("Leader is now: B2B-Node %d\n", packet->sender);
            
            crypto_init();
            util_print_uint8_hex(_b2b_aes_key, sizeof(_b2b_aes_key), 
                            "Session AES128 key: ");
            
            adv_advertising_stop();
            ui_cmd_sync_member_successful();
            return;
        }
    }
    
    /* leader sent packet */
    if(_b2b_current_leader_id == packet->sender && packet->cmd != B2B_CMD_SYNC_LEADER) {
        /* process leader command */
        if(check_cmd_counter(packet->cmd_counter, _b2b_current_cmd_counter)) {
            _b2b_current_sent_cmd = packet->cmd;
            _b2b_current_cmd_counter = packet->cmd_counter;
            ui_cmd_changed();
            adv_advertise_start();
        }

        /* process emergency command */
        if(check_cmd_counter(packet->cmd_emerg_counter, _b2b_current_cmd_emerg_counter)) {
            _b2b_current_sent_cmd_emerg = packet->cmd_emerg;
            _b2b_current_cmd_emerg_counter= packet->cmd_emerg_counter;
            adv_advertise_start();
        }
    }
}

static void prepare_b2b_packet(b2b_packet* packet, uint8_t* data, uint8_t len) {
        packet->sender = data[0+sizeof(_b2b_validation_value)];
        packet->cmd_counter =  data[1+sizeof(_b2b_validation_value)];
        packet->cmd = data[2+sizeof(_b2b_validation_value)];

        packet->cmd_emerg = B2B_CMD_NONE;
        packet->cmd_emerg_counter = 0;

        if(packet->cmd != B2B_CMD_NONE && packet->cmd != B2B_CMD_SYNC_LEADER) {
            packet->cmd_emerg_counter = data[3+sizeof(_b2b_validation_value)];
            packet->cmd_emerg = data[4+sizeof(_b2b_validation_value)];
        } else if (packet->cmd == B2B_CMD_SYNC_LEADER) {
            if(len >= B2B_AD_AES_POS + AES_KEY_SIZE) {
                memcpy(packet->aes_key, data + B2B_AD_AES_POS, AES_KEY_SIZE);
            }
        }  
        return;
}

static int check_cmd_counter(uint16_t send_cmd, uint16_t curr_cmd) {
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

    b2b_packet packet;
    
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
                            prepare_b2b_packet(&packet, data_plain, sizeof(data_plain)); 
                        }
                    } else { 

                        /* leader is not set -> expect plain data */
                        /* check alidation value */
                        if(memcmp(data.data, _b2b_validation_value, 
                            sizeof(_b2b_validation_value)) == 0) {
                            prepare_b2b_packet(&packet, data.data, data.len);
                        }
                    }

                    /* analyze packet depending on b2b type */
                    switch(_b2b_user_type) {
                        case B2B_TYPE_LEADER:
                            process_b2b_packet_leader(&packet);
                            break;
                        case B2B_TYPE_MEMBER:
                            process_b2b_packet_member(&packet);
                            break;
                        case B2B_TYPE_NONE:
                            break;
                    }
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
