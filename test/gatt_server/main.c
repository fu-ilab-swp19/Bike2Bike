#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nimble_riot.h"
#include "net/bluetil/ad.h"

#include "shell.h"
#include "shell_commands.h"
#include "host/ble_hs.h"
#include "host/util/util.h"

static const char *device_name = "RIOT calling";

static void start_advertise(void);

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

int _cmd_left(int argc, char **argv){
	
	(void) argc;
	(void) argv;	

	puts("Go Left!\n");
	uint8_t left[] = {0x00, 0x00, 0x10, 0x00};
	
	uint8_t buf[BLE_HS_ADV_MAX_SZ];
    bluetil_ad_t ad;
    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);
    bluetil_ad_add_name(&ad, device_name);

	bluetil_ad_add(&ad, BLE_GAP_AD_DEVICE_ID, left, sizeof(left));
	ble_gap_adv_set_data(ad.buf, ad.pos);
	start_advertise();
	return 0;

}

int _cmd_right(int argc, char **argv){	

	(void) argc;
	(void) argv;	

	
	puts("Go Right!\n");
	uint8_t right[] = {0x00, 0x00, 0x01, 0x00};
	
	uint8_t buf[BLE_HS_ADV_MAX_SZ];
    bluetil_ad_t ad;
    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);
    bluetil_ad_add_name(&ad, device_name);

	bluetil_ad_add(&ad, BLE_GAP_AD_DEVICE_ID, right, sizeof(right));
	ble_gap_adv_set_data(ad.buf, ad.pos);

	start_advertise();
	return 0;
}

int _cmd_guide(int argc, char **argv){		

	(void) argc;
	(void) argv;	
	

	puts("I'm your guide!\n");
	uint8_t guide[] = {0x00, 0x00, 0x00, 0x00};
	
	uint8_t buf[BLE_HS_ADV_MAX_SZ];
    bluetil_ad_t ad;
    bluetil_ad_init_with_flags(&ad, buf, sizeof(buf), BLUETIL_AD_FLAGS_DEFAULT);
    bluetil_ad_add_name(&ad, device_name);

	bluetil_ad_add(&ad, BLE_GAP_AD_DEVICE_ID, guide, sizeof(guide));
	ble_gap_adv_set_data(ad.buf, ad.pos);
	start_advertise();
	return 0;
}




static void start_advertise(void)
{
    struct ble_gap_adv_params advp;
    int rc;

    memset(&advp, 0, sizeof advp);
    advp.conn_mode = BLE_GAP_CONN_MODE_UND;
    advp.disc_mode = BLE_GAP_DISC_MODE_GEN;
    rc = ble_gap_adv_start(nimble_riot_own_addr_type, NULL, BLE_HS_FOREVER,
                           &advp, gap_event_cb, NULL);
    assert(rc == 0);
    (void)rc;
}


static const shell_command_t _commands[] = {
		{"guide", "I'm the guide", _cmd_guide},
    	{ "left", "go left", _cmd_left },
		{ "right", "go right", _cmd_right },
    	{ NULL, NULL, NULL }
};

int main(void){
	//TODO: Advertise only for a few seconds
	//TODO:	Change command does not work
	
	puts("NimBLE ready to sent\n");

	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	
 
}
