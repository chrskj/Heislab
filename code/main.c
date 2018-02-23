#include <stdio.h>

#include "elev.h"
#include "state_machine.h"
#include "buttons_handler.h"
//#include "emergency_handler.h"

int main() {
	// Initialize hardware
	if (!elev_init()) 
	{
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	printf("Press STOP button to stop elevator and exit program.\n");

    // Initialize logic
	buttons_handler_init();
	set_state(INIT);

    // Update Loop
	while (1) 
	{
		buttons_handler_update();
		update_state();
        //update_emergency();
	}

	return 0;
}
