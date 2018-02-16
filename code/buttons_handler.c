#include "buttons_handler.h"


button _command_buttons[N_FLOORS];
button _call_up_buttons[N_FLOORS-1];
button _call_down_buttons[N_FLOORS-1];


void init() 
{
	//init command_buttons
	for(int i = 0; i < N_FLOORS; i++) {
		_command_buttons[i].init(BUTTON_COMMAND, i+1);
	}
	
	//init call up/down buttons_handler
	for(int i = 0; i < N_FLOORS-1; i++) {
		_call_up_buttons[i].init(BUTTON_CALL_UP, i+1);
		_call_down_buttons[i].init(BUTTON_CALL_DOWN, i+2);
	}
}
void update() {
	for(int command_button_it = _command_buttons[0]; command_button_it <  _command_buttons[N_FLOORS]; command_button_it++) {
		
		if(elev_get_button_signal(command_button_it.get_type(), command_button_it.get_floor()) {
			command_button_it.set_active();
		}
	}
}