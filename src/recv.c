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
    printf("Start scanning environment\n");
    nimble_scanlist_clear();

    nimble_scanner_start();
    xtimer_sleep(2);
    nimble_scanner_stop();

    nimble_scanlist_entry_t* e = NULL;
    nimble_scanlist_print();

    e = nimble_scanlist_get_next(e);
    while(e) {
        bluetil_ad_t ad = BLUETIL_AD_INIT(e->ad, e->ad_len, e->ad_len);
        bluetil_ad_data_t data;
        int res = bluetil_ad_find(&ad, BLE_GAP_AD_SERVICE_DATA, &data);  

        if(res == BLUETIL_AD_OK && sizeof(data.data) >= 4) {
            if(memcmp(data.data, B2B_RECONGITION_ID, sizeof(B2B_AD_RECOGNITION_ID_SIZE)) == 0) {
                printf("Valid packet received (data size: %d) : Raw data: ", sizeof(data.data));
                for(size_t i=0; i < sizeof(data.data)+3; i++) {
                    printf("%02X ", data.data[i]);
                }
                printf("\n");
                print_b2b_packet(data.data);
            }
        } else {
            printf("Received packet but not B2B addressed\n");
        }
        e = nimble_scanlist_get_next(e);
    }   

    return 0;
}