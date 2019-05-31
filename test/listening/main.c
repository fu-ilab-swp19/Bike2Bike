#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nimble_scanner.h"
#include "nimble_scanlist.h"
#include "shell.h"
#include "shell_commands.h"


#include "xtimer.h"

/* default scan duration (1s) */
#define DEFAULT_DURATION        (1000000U)

int _cmd_scan(int argc, char **argv){


	uint32_t timeout = DEFAULT_DURATION;
	if ((argc == 2) && (memcmp(argv[1], "help", 4) == 0)) {
        	printf("usage: %s [timeout in ms]\n", argv[0]);
        return 0;
    	}
    	if (argc >= 2) {
        	timeout = (uint32_t)(atoi(argv[1]) * 1000);
    	}
	printf("Scanning for %ums now ...\n", (unsigned)(timeout / 1000));
	
	nimble_scanlist_clear();
	nimble_scanner_start();
	puts("start");
	xtimer_usleep(timeout);
	puts("timeout");
    	nimble_scanner_stop();
    	puts(" done\n\nResults:\n");
    	nimble_scanlist_print();
    	puts("DONE!\n");
	return 0;	
}

int _cmd_scan_test(int argc, char **argv){


	uint32_t timeout = DEFAULT_DURATION;
	if ((argc == 2) && (memcmp(argv[1], "help", 4) == 0)) {
        	printf("usage: %s [timeout in ms]\n", argv[0]);
        return 0;
    	}
    	if (argc >= 2) {
        	timeout = (uint32_t)(atoi(argv[1]) * 1000);
    	}
	printf("Scanning for %ums now ...\n", (unsigned)(timeout / 1000));
	
	nimble_scanlist_clear();
	nimble_scanner_start();
	puts("start");
	xtimer_usleep(timeout);
	puts("timeout");
    	nimble_scanner_stop();
    	puts(" done\n\nResults:\n");
    	nimble_scanlist_print();
    	puts("DONE!\n");
	return 0;	
}


static const shell_command_t _commands[] = {
    	{ "scan", "trigger a BLE scan", _cmd_scan },
	{ "test", "trigger a BLE scan", _cmd_scan_test },
    	{ NULL, NULL, NULL }
};

int main(void){
	/* start shell */
	//nimble_scanlist_init();
	puts("Hello World\n");
    	struct ble_gap_disc_params scan_params = {
		.itvl = BLE_GAP_LIM_DISC_SCAN_INT,
		.window = BLE_GAP_LIM_DISC_SCAN_WINDOW,
		.filter_policy = 0,                         /* don't use */
		.limited = 0,                               /* no limited discovery */
		.passive = 0,                               /* no passive scanning */
		. filter_duplicates = 0,                    /* no duplicate filtering */
	    };

	nimble_scanlist_init();
  	nimble_scanner_init(&scan_params, nimble_scanlist_update);
	char line_buf[SHELL_DEFAULT_BUFSIZE];
    	shell_run(_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

}
