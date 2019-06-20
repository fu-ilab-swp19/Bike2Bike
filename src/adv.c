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

/* sync leader has to be unencrypted for key sharing */
static int adv_advertise_sync_leader(uint8_t cmd, uint8_t sender_id, uint8_t cmd_counter) {
    bluetil_ad_t ad;

    uint8_t buf[BLE_HS_ADV_MAX_SZ];
    
    if(ble_gap_adv_active()) {
        ble_gap_adv_stop();
    }

    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);

    /*  prepare advertising name */
    bluetil_ad_add_name(&ad, B2B_ADV_NAME);

    /*  prepare our own protocol data */
    uint8_t data[B2B_AD_SIZE + AES_KEY_SIZE];
    /* validation value for checking after decrypt */
    memcpy(data, _b2b_validation_value, sizeof(_b2b_validation_value));
    /* sender id (from  package) */
    memcpy(data + sizeof(_b2b_validation_value), &sender_id, sizeof(sender_id));
    /* command counter */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id), 
                        &cmd_counter, sizeof(cmd_counter));
    /* cmd */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id)
                        + sizeof(cmd_counter), &cmd, sizeof(cmd)); 
    /* aes key used for encryption */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id)
                        + sizeof(cmd_counter) + sizeof(cmd), &_b2b_aes_key, sizeof(_b2b_aes_key));

    /* add encrypted data to the ble packet as service data */
    bluetil_ad_add(&ad, BLE_GAP_AD_SERVICE_DATA, data, sizeof(data));
    ble_gap_adv_set_data(ad.buf, ad.pos);

    _b2b_current_cmd_counter = cmd_counter;
    _b2b_current_sent_cmd = cmd;

    start_advertise();

    return 0;
}

void adv_advertising_stop(void) {
    if(ble_gap_adv_active()) {
        ble_gap_adv_stop();
        _b2b_current_sent_cmd = B2B_CMD_NONE;
    }
}
int adv_advertise_packet(uint8_t sender_id) {
    if(_b2b_current_sent_cmd == B2B_CMD_SYNC_LEADER) {
        return adv_advertise_sync_leader(_b2b_current_sent_cmd, sender_id, _b2b_current_cmd_counter);
    }
    if(_b2b_current_sent_cmd == B2B_CMD_NONE) { 
        return 0;
    }

    bluetil_ad_t ad;

    uint8_t buf[BLE_HS_ADV_MAX_SZ];

    if(ble_gap_adv_active()) {
        ble_gap_adv_stop();
    }

    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);

    /*  prepare advertising name */
    bluetil_ad_add_name(&ad, B2B_ADV_NAME);

    /*  prepare our own protocol data */
    uint8_t data[B2B_AD_SIZE];
    /* validation value for checking after decrypt */
    memcpy(data, _b2b_validation_value, sizeof(_b2b_validation_value));
    /* sender id (from  package) */
    memcpy(data + sizeof(_b2b_validation_value), &sender_id, sizeof(sender_id));
    /* command counter */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id), 
                        &_b2b_current_cmd_counter, sizeof(_b2b_current_cmd_counter));
    /* cmd */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id)
                        + sizeof(_b2b_current_cmd_counter), &_b2b_current_sent_cmd, sizeof(_b2b_current_sent_cmd));
    /*command counter emergency */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id)
                        + sizeof(_b2b_current_cmd_counter) + sizeof(_b2b_current_sent_cmd), &_b2b_current_emerg_counter,
                         sizeof(_b2b_current_emerg_counter));                     
    /*emergency cmd */
    memcpy(data + sizeof(_b2b_validation_value) + sizeof(sender_id)
                        + sizeof(_b2b_current_cmd_counter) + sizeof(_b2b_current_sent_cmd)
                        + sizeof(_b2b_current_emerg_counter), &_b2b_current_emerg_cmd, sizeof(_b2b_current_emerg_cmd)); 
    /* encrypt data */
    uint8_t data_enc[AES_BLOCK_SIZE];
    crypto_encrypt(data, data_enc);

    /* add encrypted data to the ble packet as service data */
    bluetil_ad_add(&ad, BLE_GAP_AD_SERVICE_DATA, data_enc, sizeof(data_enc));
    ble_gap_adv_set_data(ad.buf, ad.pos);

    

    start_advertise();

    return 0;
}
