#include <stdio.h>

#include "elev.h"
#include "elevator_controller.h"
#include "buttons_handler.h"
#include "stop_button.h"
#include "motor.h"
#include "door.h"
#include "floor_indicator.h"

int main() {
	// Initialize hardware
	if (!elev_init()) 
	{
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}

    // Initialize logic
    close_door();
	stop_set_inactive();
	buttons_handler_init();
	motor_init();
	set_state(INIT);

    // Update Loop
	while (1) 
	{
		update_event();
	}

	return 0;
}
