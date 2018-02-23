#include "elev.h"
#include <stdio.h>
#include "state_machine.h"
#include "buttons_handler.h"

//ToDo
//Handle  floor sensor
//Emergency stop
//handle Idle depart



int main() {
	// Initialize hardware
	if (!elev_init()) 
	{
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	buttons_handler_init();
	printf("Press STOP button to stop elevator and exit program.\n");

	elev_set_motor_direction(DIRN_UP);
	int button_pressed = 0;

	while (1) 
	{
		//handle emergensy stop
		//if(state = stop and lad || at floor): emergensy_stop_at_floor()
		//else: emergensy_stop_b_floor()
		buttons_handler_update();
		update_state();
	}

	return 0;
}
