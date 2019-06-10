#include "header/cmds.h"
#include "header/recv.h"
#include "header/adv.h"
#include "header/crypto.h"


uint32_t debounce_timer = 0;
uint8_t data1 = 1; // left
uint8_t data2 = 2; // right
uint8_t data3 = 3; // set_leader
uint8_t data4 = 4; 

void btn_handler (void *arg){
	if (xtimer_usec_from_ticks (xtimer_now()) - debounce_timer > 50000) {
		uint8_t data = *(uint8_t *) arg;
		if (data == 1) { // left "send_left"
    		_cmd_send_left(0, NULL);
		}
		if (data == 2) { // right
    		//"send_right"
			_cmd_send_right(0,NULL);
		}
		if (data == 3) { // set leader "sync_leader" 3 5
    		if (gpio_read(3) == 0 && gpio_read(5) == 0) {
					gpio_write(3,0);
					gpio_write(5,1);
				
			} else if (gpio_read(3) == 0 && gpio_read(5) == 1) {
				gpio_write(3,1);
				gpio_write(5,0);
				
			} else if (gpio_read(3) == 1 && gpio_read(5) == 0) {
						gpio_write(3,1);
						gpio_write(5,1);
				
			} else if (gpio_read(3) == 1 && gpio_read(5) == 1) {
						gpio_write(3,0);
						gpio_write(5,0);
				
			} 
			
		}
		if (data == 4) { // wait
		
		
			if (gpio_read(3) == 0 && gpio_read(5) == 0) {
				_cmd_send_stop(0,NULL);
				
			} else if (gpio_read(3) == 0 && gpio_read(5) == 1) {
				_cmd_sync_member(0,NULL);
				gpio_write(3,0);
				gpio_write(5,0);
				
			} else if (gpio_read(3) == 1 && gpio_read(5) == 0) {
				_cmd_sync_leader(0,NULL);
				gpio_write(3,0);
				gpio_write(5,0);
				
			} else if (gpio_read(3) == 1 && gpio_read(5) == 1) {
				_cmd_set_leader(0,NULL);
				gpio_write(3,0);
				gpio_write(5,0);
				
			} 
		
			
		
			//
    		//gpio_write(4,1);
		//	gpio_write(5,1);
		}
		/*
		int _cmd_set_id(int argc, char** argv);
int _cmd_set_leader(int argc, char** argv);
int _cmd_set_cmd_counter(int argc, char** argv);

int _cmd_send_left(int argc, char** argv);
int _cmd_send_right(int argc, char** argv);
int _cmd_send_stop(int argc, char** argv);
int _cmd_send_no_cmd(int argc, char** argv);

int _cmd_sync_leader(int argc, char** argv);
int _cmd_sync_member(int argc, char** argv);
		*/
	debounce_timer = xtimer_usec_from_ticks(xtimer_now ());
	}
	return ;
}



void* thread_status(int pin) {
    
    gpio_write(pin,1);
	xtimer_sleep(5);
	gpio_write(pin,0);
   
    
    //(void) arg;
    return NULL;
}


void signal_5sec(int pin) {
	thread_create(stack, sizeof(stack),
					THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_status,
                    pin, "thread");
	return;
}


void signal_left_green(void) {
	signal_5sec(2);
	return;
}
void signal_right_green(void) {
	signal_5sec(4);
	return;
}
void signal_left_red(void) {
	signal_5sec(3);
	return;
}
void signal_right_red(void) {
	signal_5sec(5);
	return;
}
void signal_status_green(void) {
	signal_5sec(0);
	return;
}
void signal_status_red(void) {
	signal_5sec(1);
	return;
}
void set_status_red(void) {
	gpio_write(1,1);
	return;
}
void set_status_green(void) {
	gpio_write(0,1);
	return;
}
void reset_status(void) {
	gpio_write(0,1);
	return;
}



void led_init(void) {
	// Init output Pins

    gpio_init(0,GPIO_OUT); // status green
    gpio_init(1,GPIO_OUT); //status red

    gpio_init(2,GPIO_OUT); // left green
    gpio_init(3,GPIO_OUT); // left red
	
    gpio_init(4,GPIO_OUT); // right green
    gpio_init(5,GPIO_OUT); // right red
	
	// set all leds to off
	
	gpio_write(0,0);
	gpio_write(1,0);
	gpio_write(2,0);
	gpio_write(3,0);
	gpio_write(4,0);
	gpio_write(5,0);
	
	// init button handler
	

	gpio_init_int(7,GPIO_IN,GPIO_FALLING,btn_handler,&data1);
	
	gpio_init_int(8,GPIO_IN,GPIO_FALLING,btn_handler,&data2);
	
	gpio_init_int(9,GPIO_IN,GPIO_FALLING,btn_handler,&data3);

	gpio_init_int(10,GPIO_IN,GPIO_FALLING,btn_handler,&data4);
}