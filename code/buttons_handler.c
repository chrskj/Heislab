#include "buttons_handler.h"
#define N_BUTTONS N_FLOORS+(N_FLOORS-1)*2
//Commands Up Down
//  ****  ***  ***

button _buttons[N_BUTTONS];

void buttons_handler_init() 
{
	//init command_buttons
	for(int i = 0; i < N_FLOORS; i++) 
	{
		button_init(_buttons + i, BUTTON_COMMAND, i);
	}
	
	//init call up/down buttons_handler
	for(int i = 0; i < N_FLOORS-1; i++) 
	{
		button_init(_buttons + i + N_FLOORS, BUTTON_CALL_UP, i);
		button_init(_buttons + i + N_FLOORS*2-1 , BUTTON_CALL_DOWN, i+1);
	}
}
void buttons_handler_update() 
{
	
	for(int i = 0; i < N_BUTTONS; i++) 
	{	
		if(elev_get_button_signal(button_get_type(_buttons+i), button_get_floor(_buttons+i)))
		{	
			button_set_active(_buttons+i);
		}
	}
}

void turn_buttons_on_floor_off(int floor) 
{
	for(int i = 0; i < N_BUTTONS; i++) 
	{	
		
		if(button_get_floor(_buttons+i) == floor)
		{	
			button_set_inactive(_buttons+i);
		}
	}

}

elev_motor_direction_t get_request_direction(int floor)
{
	for(int i = 0; i < N_BUTTONS; i++) 
    {
		if(button_is_active(_buttons + i)) 
        {
            if(button_get_floor(_buttons + i) > floor) 
            {
                return DIRN_UP;
            } else if(button_get_floor(_buttons+i) < floor) 
            {
                return DIRN_DOWN;
            }
        }
    } 
    return DIRN_STOP;
}

bool is_button_active_on_floor(int floor) {
	for(int i = 0; i < N_BUTTONS; i++) 
	{	
		if(button_get_floor(_buttons+i) == floor && button_is_active(_buttons +i))
		{	
			return true;
		}
	}
	return false;
}
