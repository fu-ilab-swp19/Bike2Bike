#include "header/adv.h"


static int gap_event_cb(struct ble_gap_event *event, void *arg);

static void start_advertise(void)
{
    struct ble_gap_adv_params advp;
    int rc;

    memset(&advp, 0, sizeof advp);
    advp.conn_mode = BLE_GAP_CONN_MODE_NON;
    advp.disc_mode = BLE_GAP_DISC_MODE_GEN;
    rc = ble_gap_adv_start(nimble_riot_own_addr_type, NULL, BLE_HS_FOREVER,
                           &advp, gap_event_cb, NULL);
    assert(rc == 0);
    (void)rc;
}

static int gap_event_cb(struct ble_gap_event *event, void *arg)
{
    (void)arg;

    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            if (event->connect.status) {
                start_advertise();
            }
            break;

        case BLE_GAP_EVENT_DISCONNECT:
            start_advertise();
            break;
    }
    return 0;
}

int adv_advertise_packet(uint8_t cmd, uint8_t sender_id, uint8_t cmd_counter) {
    bluetil_ad_t ad;

    uint8_t buf[BLE_HS_ADV_MAX_SZ];
    
    if(ble_gap_adv_active()) {
        ble_gap_adv_stop();
    }

    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);

    // prepare advertising name
    char name[get_own_id_length() + sizeof(B2B_ADV_NAME)];

    snprintf(name, sizeof(name), "%s%i", B2B_ADV_NAME, _b2b_own_id); 
    bluetil_ad_add_name(&ad, name);

    // prepare our own protocol data
    uint8_t data[B2B_AD_RECOGNITION_ID_SIZE + B2B_AD_SIZE];
    // bike2bike recognition id
    memcpy(data, B2B_RECONGITION_ID, sizeof(B2B_RECONGITION_ID));
    // sender id (from  package)
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE, &sender_id, sizeof(sender_id));
    // command counter
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE + sizeof(sender_id), &cmd_counter, sizeof(cmd_counter));
    // cmd
    memcpy(data + B2B_AD_RECOGNITION_ID_SIZE + sizeof(sender_id) + sizeof(cmd_counter), &cmd, sizeof(cmd)); 

    printf("Raw data: ");
    for(size_t i = 0; i < sizeof(data); i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    printf("Data size: %d\n", sizeof(data));
    bluetil_ad_add(&ad, BLE_GAP_AD_SERVICE_DATA, data, sizeof(data));
 
    ble_gap_adv_set_data(ad.buf, ad.pos);
    start_advertise();

    return 0;
}




