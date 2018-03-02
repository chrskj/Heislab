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

    // Initialize logic
	buttons_handler_init();
	set_state(INIT);

    // Update Loop
	while (1) 
	{
		update_event();
	}

	return 0;
}
