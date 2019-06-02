#include "header/adv.h"

int adv_prepare_package(uint8_t cmd) {
    bluetil_ad_t ad;

    uint8_t buf[B2B_AD_SIZE + B2B_AD_RECOGNITION_ID_SIZE];
    bluetil_ad_init_with_flags(&ad,  buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);
    
    // prepare advertising name
    char name[20];
    snprintf(name, sizeof(name), "%s", B2B_ADV_NAME); 
    bluetil_ad_add_name(&ad, name);

    (void)cmd;
    return 0;
}

