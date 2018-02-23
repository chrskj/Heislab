#include "state_machine.h"

Timer timer;
elevator_state_t state;
elev_motor_direction_t elevator_direction;
int floor_indicator;

void arrive_at_floor(); 
void depart_from_floor();
void set_motor_direction(elev_motor_direction_t direction); 

void update_state() 
{
	switch (state){
		case(MOVING):
			printf("going up\n");

			int floor_sensor = elev_get_floor_sensor_signal();
			if(floor_sensor != floor_indicator && floor_sensor != -1) 
			{
				if(is_button_active_on_floor(floor_sensor)) 
				{
					arrive_at_floor();
				}
			}
				//Arrive at floor
			
		break;
		case(STOP_AND_LOAD):
			printf("stop and load\n");
			if(time_is_up(&timer)) 
			{
				depart_from_floor();
			}
		break;
		case(IDLE):
			printf("idle\n");
			elev_motor_direction_t activity_listener = prefered_direction(floor_indicator, elevator_direction);
			if(activity_listener != DIRN_STOP) 
			{
				set_motor_direction(prefered_direction(floor_indicator, elevator_direction));
				if(elevator_direction == DIRN_UP || elevator_direction == DIRN_DOWN) {
					state = MOVING;
				} else{
					state = IDLE;
				}
			}
			
		break;
		case(EMERGENCY_STOP_FLOOR):
			printf("emergency stop on floor\n");
			//ev_set_motor_direction(DIRN_STOP);
			//if 
		break;
		case(EMERGENCY_STOP_B_FLOOR):
			printf("emergency stop between floor\n");
		break;
		default:
			printf("Error, unkonwn state");				
	}
}

void arrive_at_floor() 
{

	set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	start_timer(&timer, 3);
	state = STOP_AND_LOAD;
	floor_indicator = elev_get_floor_sensor_signal();
	turn_buttons_on_floor_off(floor_indicator);
	elev_set_floor_indicator(floor_indicator);
	//Update floorlight
}

void depart_from_floor()
{
	elev_set_door_open_lamp(0);
	set_motor_direction(prefered_direction(floor_indicator, elevator_direction));
	if(elevator_direction == DIRN_UP || elevator_direction == DIRN_DOWN) {
		state = MOVING;
	} else{
		state = IDLE;
	}
}

void set_motor_direction(elev_motor_direction_t direction) {
	elevator_direction = direction;
	elev_set_motor_direction(direction);
}

void set_state(elevator_state_t elevator_state)
{

}
