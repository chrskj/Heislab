#include "buttons_handler.h"


button _command_buttons[N_FLOORS];
button _call_up_buttons[N_FLOORS-1];
button _call_down_buttons[N_FLOORS-1];


void buttons_handler_init() 
{
	//init command_buttons
	for(int i = 0; i < N_FLOORS; i++) {
		button_init(_command_buttons + i, BUTTON_COMMAND, i+1);
	}
	
	//init call up/down buttons_handler
	for(int i = 0; i < N_FLOORS-1; i++) {
		button_init(_call_up_buttons+i, BUTTON_CALL_UP, i+1);
		button_init(_call_down_buttons + i, BUTTON_CALL_DOWN, i+2);
	}
}
void buttons_handler_update() {
	for(button * command_button_it = _command_buttons; command_button_it <  _command_buttons+N_FLOORS; command_button_it++) {
		
		if(elev_get_button_signal(button_get_type(command_button_it), button_get_floor(command_button_it))) {
			button_set_active(command_button_it);
		}
	}
}