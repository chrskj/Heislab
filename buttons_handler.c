#include "buttons_handler.h"
#define N_BUTTONS N_FLOORS+(N_FLOORS-1)*2


#define TOP_FLOOR N_FLOORS
#define BUTTOM_FLOOR 0

//Array of all buttons not including emergency button 
button _buttons[N_BUTTONS];

//Determine if the button direction is the same as elevator direction
bool is_same_direction(button * button_p, elev_motor_direction_t direction);

//Determine if button is the highest or lowest button witch is also active
bool is_extremist_button_request(button * button_p, elev_motor_direction_t direction);


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
		button_init(_buttons + i + N_FLOORS * 2-1 , BUTTON_CALL_DOWN, i+1);
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

elev_motor_direction_t get_request_direction(int floor, elev_motor_direction_t direction)
{
	if(direction == DIRN_UP || direction == DIRN_STOP) 
	{
		bool to_go_down = false;
		for(int i = 0; i < N_BUTTONS; i++) 
		{	
			
			if(button_is_active(_buttons +i)) 
			{
				if(button_get_floor(_buttons+i) > floor) {
					return DIRN_UP;
				} else if(button_get_floor(_buttons+i) < floor) {
					to_go_down = true;
				}
			}
		}
		if(to_go_down) 
		{
			return DIRN_DOWN;
		}
	} else 
	{
		bool to_go_up = false;
		for(int i = 0; i < N_BUTTONS; i++) 
		{	
			if(button_is_active(_buttons +i)) 
			{
				if(button_get_floor(_buttons+i) < floor) {
					return DIRN_DOWN;
				}else if(button_get_floor(_buttons+i) >floor) {
					to_go_up = true;
				}
			}
		}
		if(to_go_up) 
		{
			return DIRN_UP;
		}
	}
	return DIRN_STOP;
}

bool is_button_active_on_floor(int floor) 
{
	for(int i = 0; i < N_BUTTONS; i++) 
	{	
		if(button_get_floor(_buttons+i) == floor && button_is_active(_buttons +i))
		{	
			return true;
		}
	}
	return false;
}

bool to_stop_on_floor(int floor, elev_motor_direction_t direction) 
{
	for(int i = 0; i < N_BUTTONS; i++) //bla gjennom alle knapper
	{
        if(button_is_active(_buttons+i) && button_get_floor(_buttons+i) == floor) //If Floor == elevator floor
       	{

           if(	is_same_direction(_buttons+i, direction) || 
            	button_get_type(_buttons+i) == BUTTON_COMMAND || 
            	is_extremist_button_request(_buttons+i, direction)) 
            {
            	return true;
            
       		}
       	}
       	if((button_get_floor(_buttons+i) == BUTTOM_FLOOR || button_get_floor(_buttons+i) == TOP_FLOOR) 
       		&& button_get_floor(_buttons+i) == floor)
       	{
       		return true;
       	}
	}
    return false;
}

bool is_same_direction(button * button_p, elev_motor_direction_t direction) 
{
	return (button_get_type(button_p) == BUTTON_CALL_UP && direction == DIRN_UP) ||
	(button_get_type(button_p) == BUTTON_CALL_DOWN && direction == DIRN_DOWN);
}

bool is_extremist_button_request(button * button_p, elev_motor_direction_t direction) 
{
	if(direction == DIRN_UP) 
	{
		for(int i = 0; i < N_BUTTONS; i++) 
		{
			if(button_get_floor(button_p)<button_get_floor(_buttons+i) && button_is_active(_buttons+i))
            {
				return false;
			}
		}
		
	}
	else if(direction == DIRN_DOWN) 
	{
		for(int i = 0; i < N_BUTTONS; i++) 
		{
			if(button_get_floor(button_p)>button_get_floor(_buttons+i) && button_is_active(_buttons+i)) 
			{
				return false;
			}
		}
		
	} else {
		printf("Direction error\n");
	}
	printf("Extrimist floor\n");
	return true;
}

void remove_all_requests() 
{
	for(int i = 0; i < N_BUTTONS; i++) 
	{
		button_set_inactive(_buttons+i);
	}
}

elev_motor_direction_t find_direction_after_emergency(int current_floor, int desired_floor, elev_motor_direction_t prev_direction) 
{
	if(prev_direction == DIRN_UP)
    {
		if(current_floor>=desired_floor) 
		{
			return DIRN_DOWN;
		} 
	}
    else if(prev_direction == DIRN_DOWN) 
	{
		if(current_floor>desired_floor)
        {
			return DIRN_DOWN;
		}
	}
	return DIRN_UP;
}

// Returns the first active floor that is found
int get_first_active_floor()
{
	for(int i = 0; i < N_BUTTONS; i++) 
	{
		if(button_is_active(_buttons+i))
		{
			return button_get_floor(_buttons+i);
		}
	}
	return -1;
}
