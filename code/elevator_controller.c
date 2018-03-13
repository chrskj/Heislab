#include "elevator_controller.h"

elevator_state_t state;

//Sets state to moving if any button is pressed while waiting between floors
bool check_moving_from_b_floor()
{
    int desired_floor = get_first_active_floor();
    float precise_floor = get_precise_floor();
    if(desired_floor != -1) 
    {
    	if (desired_floor > precise_floor)
    	{
    		motor_set_direction(DIRN_UP);
        	set_state(MOVING);
    	}
    	else
    	{
    		motor_set_direction(DIRN_DOWN);
        	set_state(MOVING);
    	}
        return 1;
    }
    return 0;
}

//Checks if elevator is on a floor which it hasn't stopped at that meets the requirements from another function for entering state STOP_AND_LOAD
bool check_stop_on_floor()
{
    int floor_sensor = elev_get_floor_sensor_signal();
    if (floor_sensor == -1)
    {
        set_stopped_at_floor(false);
    }
    if(!get_stopped_at_floor() && floor_sensor != -1) 
    {
        if(to_stop_on_floor(floor_sensor, motor_get_current_direction())) 
        {
            set_state(STOP_AND_LOAD);
            return true;
        }
    }
    return false;			
}

//While moving in state INIT check if elevator has arrived at floor and set state to WAIT_FOR_REQUEST
bool check_if_arrived_floor()
{
    if(elev_get_floor_sensor_signal() != -1)
    {
        set_state(WAIT_FOR_REQUEST);
        return true;
    }
    return false;
}

//Checks if timer for door has run out, if so the state is set to WAIT_FOR_REQUEST
bool check_waiting_for_request()
{
    if(time_is_up()) 
    {
        set_state(WAIT_FOR_REQUEST);
        return true;
    }
    return false;
}

//Check sensors and if button activated on same floor set state to STOP_AND_LOAD
bool check_load_on_floor() 
{
    if(is_button_active_on_floor(get_floor())) 
    {
        set_state(STOP_AND_LOAD);
        return true;
    }
    return false;
}

//Check sensors and if any buttons in pressed set state to MOVING with direction based on logic from another function
bool check_moving()
{
        elev_motor_direction_t activity_listener = get_request_direction(get_floor(), motor_get_prev_direction());
        if(activity_listener == DIRN_DOWN) 
        {
            motor_set_direction(DIRN_DOWN);
            set_state(MOVING);
            return true;
        }
        else if(activity_listener == DIRN_UP) 
        {
            motor_set_direction(DIRN_UP);
            set_state(MOVING);
            return true;
        }
        return false;
}

// Checks emergency
bool check_emergency()
{
    if(elev_get_floor_sensor_signal() != -1 && stop_is_active())
    {
        set_state(EMERGENCY_STOP_FLOOR);
        return true;
    }
    else if(stop_is_active())
    {
        set_state(EMERGENCY_STOP_B_FLOOR);
        return true;
    }
    return false;
}

//Check if emergency button is relesed to end EMERGENCY state
bool check_emergency_released()
{
	if (!stop_is_active())
	{
		if (state == EMERGENCY_STOP_B_FLOOR)
		{
			set_state(WAIT_FOR_REQUEST_B_FLOOR);
		}
		else if (time_is_up())
		{
            close_door();
            set_state(WAIT_FOR_REQUEST);	
		}
		return true;
	}
    else
    {
        start_timer(3);
    	return false;
    }
}

void update_event() 
{
	switch(state)
    {
		case(MOVING):
        {
        	stop_button_update();
            buttons_handler_update();
            update_floor_indicator();
            update_precise_floor_indicator();
            if( 
                    check_emergency() || 
                    check_stop_on_floor())
                    break;
            break;
        }
		case(STOP_AND_LOAD):
        {
        	stop_button_update();
            buttons_handler_update();
            if(is_button_active_on_floor(get_floor())) 
            {
                start_timer(3);
                turn_buttons_on_floor_off(get_floor());
            }
            if(
                    check_emergency() ||
                    check_waiting_for_request())
		    break;
            break;
        }
		case(WAIT_FOR_REQUEST):
        {
        	stop_button_update();
            buttons_handler_update();
            if(
                    check_emergency() ||
                    check_load_on_floor() ||
                    check_moving())
		            break;
            break;
        }
        case(WAIT_FOR_REQUEST_B_FLOOR):
        {
        	stop_button_update();
            buttons_handler_update();
            if(
                    check_emergency() ||
                    check_moving_from_b_floor())
            break;
            break;
        }
		case(EMERGENCY_STOP_FLOOR):
        {
        	stop_button_update();
            buttons_handler_update();
            if(
                    check_emergency_released())
            break;
            break;
        }
		case(EMERGENCY_STOP_B_FLOOR):
        {
        	stop_button_update();
            buttons_handler_update();
            if(
                    check_emergency_released())
            break;
            break;
        }
		case(INIT):
        {
        	stop_button_update();
            if(
                    check_emergency() ||
                    check_if_arrived_floor())
            break;
            break;
        }
		default:
        {
			printf("Error, unkonwn state");   
        }
	}
}

void set_state(elevator_state_t elevator_state)
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
            update_floor_indicator();
            motor_set_direction(DIRN_STOP);
            open_door();
            start_timer(3);
            set_stopped_at_floor(true);
            turn_buttons_on_floor_off(get_floor());
            break;
        }
        case(WAIT_FOR_REQUEST):
        {
            printf("Waiting for request\n");
        	stop_set_inactive();
            update_floor_indicator();
            close_door();
            motor_set_direction(DIRN_STOP);
            break;
        }
        case(WAIT_FOR_REQUEST_B_FLOOR):
        {
            printf("Waiting for request between floor\n");
        	stop_set_inactive();
            close_door();
            motor_set_direction(DIRN_STOP);
            break;
        }
        case(EMERGENCY_STOP_B_FLOOR):
        {
            printf("Emergency stop between floors\n");
        	stop_set_active();
    		motor_set_direction(DIRN_STOP);
            break;
        }
        case(EMERGENCY_STOP_FLOOR):
        {
            printf("Emergency stop at floor\n");
        	stop_set_active();
        	open_door();
    		motor_set_direction(DIRN_STOP);
            break;
        }
        case(INIT):
        {
            printf("Initialize\n");
            motor_set_direction(DIRN_UP);
            break;
        }
        default:
        {
            printf("Error, unkonwn event");   
        }
    }
}

elevator_state_t get_state()
{
	return state;
}
