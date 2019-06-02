#include "header/adv.h"

int adv_prepare_package(uint8_t cmd, uint8_t sender_id, uint8_t cmd_counter) {
    bluetil_ad_t ad;

    uint8_t buf[B2B_AD_SIZE + B2B_AD_RECOGNITION_ID_SIZE];
    bluetil_ad_init_with_flags(&ad,  buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);
    
    // prepare advertising name
    char name[20];
    snprintf(name, sizeof(name), "%s", B2B_ADV_NAME); 
    bluetil_ad_add_name(&ad, name);

    // prepare our own protocol data
    uint8_t data[B2B_AD_RECOGNITION_ID_SIZE + B2B_AD_SIZE];
    // bike2bike recognition id
    memcpy(data, B2B_RECONGITION_ID, sizeof(B2B_RECONGITION_ID));
    // sender id (from package)
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE, &sender_id, sizeof(sender_id));
    // command counter
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE + sizeof(sender_id), &cmd_counter, sizeof(cmd_counter));
    // cmd
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE + sizeof(sender_id) + sizeof(cmd_counter), &cmd, sizeof(cmd)); 

    ble_gap_adv_set_data(ad.buf, ad.pos);

    return 0;
}

