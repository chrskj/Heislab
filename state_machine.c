#include "state_machine.h"

Timer timer;
elevator_state_t state;
elev_motor_direction_t elevator_direction;
int floor_indicator;

void arrive_at_floor(); 
void depart_from_floor();
void set_motor_direction(elev_motor_direction_t direction); 

void update_event() 
{
	switch(state)
    {
		case(MOVING):
        {
<<<<<<< HEAD
            check_stop_and_load();
            check_error();
            break;
        }
		case(STOP_AND_LOAD):
        {
            check_error();
            check_idle();
		    break;
        }
		case(IDLE):
        {
            check_stop_and_load();
            check_moving();
            check_error();
		    break;
        }
		case(EMERGENCY_STOP_FLOOR):
        {
            check_error_button_realeased_at_floor();
            break;
        }
		case(EMERGENCY_STOP_B_FLOOR):
        {
            check_error_button_realeased_between_floor();
            break;
        }
		case(INIT):
        {
            check_if_floor();
            break;
        }
		default:
        {
			printf("Error, unkonwn event");   
            break;
=======
			int floor_sensor = elev_get_floor_sensor_signal();
			if(floor_sensor != floor_indicator && floor_sensor != -1) 
			{
				if(is_button_active_on_floor(floor_sensor)) 
				{
					arrive_at_floor();
				}
			}			
		break;
        }
		case(STOP_AND_LOAD):
        {
			if(time_is_up(&timer)) 
			{
				depart_from_floor();
			}
		break;
        }
		case(IDLE):
        {
			elev_motor_direction_t activity_listener = prefered_direction(floor_indicator, elevator_direction);
			if(activity_listener != DIRN_STOP) 
			{
				set_motor_direction(prefered_direction(floor_indicator, elevator_direction));
				if(elevator_direction == DIRN_UP || elevator_direction == DIRN_DOWN) 
                {
					set_state(MOVING);
				} else
                {
					set_state(IDLE);
				}
			}
		break;
        }
		case(EMERGENCY_STOP_FLOOR):
        {
            int temp = 1;
			//ev_set_motor_direction(DIRN_STOP);
			//if 
		break;
        }
		case(EMERGENCY_STOP_B_FLOOR):
        {
            int temp = 1;
		break;
        }
		case(INIT):
        {
			set_motor_direction(DIRN_UP);
			if(elev_get_floor_sensor_signal() != -1)
            {
				stop_at_floor();
			}
		break;
        }
		default:
        {
			printf("Error, unkonwn state");   
>>>>>>> fb83a6249525b43e562f6a69c2a0e1312dfab7a0
        }
	}
}

void update_state(elevator_state_t elevator_state)
{
	state = elevator_state;
    switch(state)
    {
        case(MOVING):
        {
            printf("Moving\n");
            break;
        }
        case(STOP_AND_LOAD):
        {
            printf("Stop and load\n");
            set_motor_direction(DIRN_STOP);
            elev_set_door_open_lamp(1);
            start_timer(&timer, 3);
            floor_indicator = elev_get_floor_sensor_signal();
            turn_buttons_on_floor_off(floor_indicator);
            elev_set_floor_indicator(floor_indicator);
            //Update floorlight       
            break;
        }
        case(IDLE):
        {
            printf("Idle\n");
            elev_set_door_open_lamp(0);
            set_motor_direction(DIRN_STOP);
            floor_indicator = elev_get_floor_sensor_signal();
            elev_set_floor_indicator(floor_indicator);
            //Update floorlight
            break;
        }
        case(EMERGENCY_STOP_B_FLOOR):
        {
            printf("Emergency stop between floors\n");
            break;
        }
        case(EMERGENCY_STOP_FLOOR):
        {
            printf("Emergency stop at floor\n");
            break;
        }
        case(INIT):
        {
            printf("Initialize\n");
            set_motor_direction(DIRN_UP);
            break;
        }
        default:
        {
            printf("Error, unkonwn event");   
        }
    }
}

// Checks if elevator is at a floor which has been requested
void check_stop_and_load()
{
    int floor_sensor = elev_get_floor_sensor_signal();
    if(floor_sensor != floor_indicator && floor_sensor != -1) 
    {
        if(is_button_active_on_floor(floor_sensor) && check_preferred_stop()) 
        {
            update_state(STOP_AND_LOAD);
        }
    }			
}


// Todo: Make prio list for if elevator should stop on floor
// Same direction same way request > end floor same direction request > same direction opposite way request > opposite direction request
bool check_preferred_stop()
{
    return true;
}

void check_if_floor()
{
    if(elev_get_floor_sensor_signal() != -1)
    {
        update_state(IDLE);
    }
}

void check_idle()
{
    if(time_is_up(&timer)) 
    {
        update_state(IDLE);
    }
}

void check_moving()
{
        elev_motor_direction_t activity_listener = get_request_direction(floor_indicator);
        if(activity_listener == DIRN_DOWN) 
        {
            set_motor_direction(DIRN_DOWN);
            update_state(MOVING);
        }
        else if(activity_listener == DIRN_UP) 
        {
            set_motor_direction(DIRN_UP);
            update_state(MOVING);
        }
}

void check_error()
{

}

void set_motor_direction(elev_motor_direction_t direction) 
{
	elevator_direction = direction;
	elev_set_motor_direction(direction);
}

elevator_state_t get_state()
{
    return state;
}

	state = elevator_state;
    switch(state)
    {
    case(MOVING):
        printf("Moving\n");
        break;
    case(IDLE):
        printf("Idle\n");
        break;
    case(STOP_AND_LOAD):
        printf("Stop and load\n");
        break;
    case(EMERGENCY_STOP_B_FLOOR):
        printf("Emergency stop between floors\n");
        break;
    case(EMERGENCY_STOP_FLOOR):
        printf("Emergency stop at floor\n");
        break;
    case(INIT):
        printf("Initialize\n");
        break;
    default:
        break;
    }
}

elevator_state_t get_state()
{
    return state;
}


