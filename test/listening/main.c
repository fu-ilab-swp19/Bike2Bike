#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xtimer.h"
#include "shell.h"
#include "shell_commands.h"

#include "net/bluetil/ad.h"
#include "nimble_scanner.h"
#include "nimble_scanlist.h"

#define DEFAULT_DURATION        (3)

const uint8_t B2B_ID[] = {0x13, 0x37};

int _cmd_scan(int argc, char ** argv) {
    printf("%02X", B2B_ID[0]);
    printf("%02X\n", B2B_ID[1]);
    nimble_scanlist_entry_t* entry = NULL;
    for(int i = 0; i < 10; i++) {
        nimble_scanlist_clear();
        printf("Scanning...\n");
        printf("------------------\n");
        nimble_scanner_start();
        xtimer_sleep(3);
        nimble_scanner_stop();
        entry = nimble_scanlist_get_next(entry);
        while(entry) {
            bluetil_ad_t ad = BLUETIL_AD_INIT(entry->ad, entry->ad_len, entry->ad_len);
            char name[(BLE_ADV_PDU_LEN + 1)] = {0};
            bluetil_ad_data_t company_id;
            int res = bluetil_ad_find_str(&ad, BLE_GAP_AD_NAME, name, sizeof(name));

            bluetil_ad_find(&ad, BLE_GAP_AD_VENDOR, &company_id);

            if (res != BLUETIL_AD_OK) {
                res = bluetil_ad_find_str(&ad, BLE_GAP_AD_NAME_SHORT, name, sizeof(name));
            }
            
            if(res == BLUETIL_AD_OK && company_id.len >= sizeof(B2B_ID)) {
                if(memcmp(company_id.data, (void*)B2B_ID, sizeof(B2B_ID)) == 0) {
                    printf("Device name: %s\n", name);
                    printf("Raw data: ");
                    for(uint8_t i = 0; i < entry->ad_len; i++) {
                        printf("%02X", entry->ad[i]);
                    }
                    printf("\nCompany id: ");
                    for(size_t i = 0; i < company_id.len; i++) {
                        if(i == 2) {
                            printf("\nData: ");
                        }
                        printf("%02X", company_id.data[i]);
                        
                    }
                    printf("\n------------------\n");
                }
            }
            entry = nimble_scanlist_get_next(entry);
        }
        printf("Scanning completed. Loop %i from 10. Sleeping 10sec now...\n", i);
        xtimer_sleep(10);
    }
    (void)argc;
    (void)argv;
    return 0;
}

static const shell_command_t _commands[] = {
    { "scan", "trigger a BLE scan", _cmd_scan },
    { NULL, NULL, NULL }
};

int main (void) {
    puts("Bike2Bike Listening Program");
    struct ble_gap_disc_params scan_params = {
        .itvl = BLE_GAP_LIM_DISC_SCAN_INT,
        .window = BLE_GAP_LIM_DISC_SCAN_WINDOW,
        .filter_policy = 0,                         
        .limited = 0,                               
        .passive = 0,                               
        . filter_duplicates = 0,                    
    };  

    /* initialize the nimble scanner */
    nimble_scanlist_init();
    nimble_scanner_init(&scan_params, nimble_scanlist_update);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}


