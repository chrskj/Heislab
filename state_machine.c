#include "state_machine.h"

Timer timer;
elevator_state_t state;
elev_motor_direction_t prev_direction;
bool stopped_at_floor = false;
bool emergency_is_pressed = false;
int floor_indicator;

void arrive_at_floor(); 
void depart_from_floor();
void set_motor_direction(elev_motor_direction_t direction); 
<<<<<<< HEAD
void update_floor_indicator_light();
=======

//Check buttons and if conditons met goto WAIT_FOR_REQUEST state
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
bool check_waiting_for_request();

//Check sensors and if conditons while moving met stop elevator and set state to STOP_AND_LOAD
bool check_stop_on_floor();

//Check sensors and if button activated on same floor set state to STOP_AND_LOAD
bool check_load_on_floor();

//Check sensors and if any buttons in pressed set state to MOVING
bool check_moving();
<<<<<<< HEAD
bool check_if_floor();
bool check_button_released();
=======

//While moving in state INIT check if elevator has arrived at floor and set state to WAIT_FOR_REQUEST
bool check_if_arrived_floor();

//Check if emergency button is relesed to end EMERGENCY state
bool check_emergency_button_released();

//Check if emergency button is pressed to enter EMERGENCY state
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
bool check_emergency();
bool wait_for_first_request();

<<<<<<< HEAD
// Updates which events the state will check
=======
//update light that indicates current floor
void update_floor_indicator_light();

//while waiting for reqest between floors check if any buttons is pressed and set state to MOVING
bool  check_moving_form_b_floor();

>>>>>>> 31bd143da96358c10569563821b490537951c1c9
void update_event() 
{
	switch(state)
    {
		case(MOVING):
        {
            buttons_handler_update();
            update_floor_indicator_light();
            if( 
            check_emergency() || 
            check_stop_on_floor())
            break;
            break;

        }
		case(STOP_AND_LOAD):
        {
            buttons_handler_update();
            if(is_button_active_on_floor(floor_indicator)) 
            {
                start_timer(&timer, 3);
                turn_buttons_on_floor_off(floor_indicator);
            }
            if(
            check_emergency() ||
            check_waiting_for_request())
		    break;
            break;

        }
		case(WAIT_FOR_REQUEST):
        {
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
            buttons_handler_update();
            if(
            check_emergency() ||
<<<<<<< HEAD
            wait_for_first_request())
=======
             check_moving_form_b_floor())
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
            break;
            break;
        }
		case(EMERGENCY_STOP_FLOOR):
        {

            if(
             check_emergency_button_released())
            break;
            break;

        }
		case(EMERGENCY_STOP_B_FLOOR):
        {
            if(
             check_emergency_button_released())
            break;
            break;

        }
		case(INIT):
        {
            if(
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

// Sets the state of the elevator and performs actions for that state
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
            update_floor_indicator_light();
            set_motor_direction(DIRN_STOP);
            elev_set_door_open_lamp(1);
            start_timer(&timer, 3);
            stopped_at_floor = true;
            floor_indicator = elev_get_floor_sensor_signal();
            turn_buttons_on_floor_off(floor_indicator);
            
            //Update floorlight       
            break;
        }
        case(WAIT_FOR_REQUEST):
        {
            printf("Waiting for request\n");
            floor_indicator = elev_get_floor_sensor_signal();
            elev_set_stop_lamp(0);
            update_floor_indicator_light();
            elev_set_door_open_lamp(0);
            set_motor_direction(DIRN_STOP);
            floor_indicator = elev_get_floor_sensor_signal();
            //Update floorlight
            break;
        }
        case(WAIT_FOR_REQUEST_B_FLOOR):
        {
            printf("Waiting for request between floor\n");
            elev_set_stop_lamp(0);
            elev_set_door_open_lamp(0);
            set_motor_direction(DIRN_STOP);
            //Update floorlight
            break;
        }
        case(EMERGENCY_STOP_B_FLOOR):
        {
            printf("Emergency stop between floors\n");
            elev_set_stop_lamp(1);
            remove_all_requests();
            set_motor_direction(DIRN_STOP);
            elev_set_door_open_lamp(0);
            emergency_is_pressed = true;
            break;
        }
        case(EMERGENCY_STOP_FLOOR):
        {
            printf("Emergency stop at floor\n");
            elev_set_stop_lamp(1);
            remove_all_requests();
            set_motor_direction(DIRN_STOP);
            elev_set_door_open_lamp(1);
            emergency_is_pressed = true;
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
<<<<<<< HEAD

// Sets direction towards the first request it finds and sets state to moving
bool wait_for_first_request() 
{
=======
bool  check_moving_form_b_floor() {
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
    int desired_floor = get_first_active_floor();
    if(desired_floor!= -1)
    {
        prev_direction = find_direction_after_emergency(floor_indicator, desired_floor, prev_direction);
        set_motor_direction(prev_direction);
        set_state(MOVING);
        return 1;
    }
    return 0;
}

<<<<<<< HEAD
// Checks if elevator is at a floor which has been requested
=======

>>>>>>> 31bd143da96358c10569563821b490537951c1c9
bool check_stop_on_floor()
{
    int floor_sensor = elev_get_floor_sensor_signal();
    if (floor_sensor == -1)
    {
        stopped_at_floor = false;
    }
    if(!stopped_at_floor && floor_sensor != -1) 
    {
        if(to_stop_on_floor(floor_sensor, prev_direction)) 
        {
            set_state(STOP_AND_LOAD);
            return true;
        }
    }
    return false;			
}

<<<<<<< HEAD
// Sets state to WAIT_FOR_REQUEST if a floor is found
bool check_if_floor()
=======
bool check_if_arrived_floor()
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
{
    if(elev_get_floor_sensor_signal() != -1)
    {
        set_state(WAIT_FOR_REQUEST);
        return true;
    }
    return false;
}

// Sets state to WAIT_FOR_REQUEST if timer has run out
bool check_waiting_for_request()
{
    if(time_is_up(&timer)) 
    {
        set_state(WAIT_FOR_REQUEST);
        return true;
    }
    return false;
}

// Sets state to STOP_AND_LOAD if visited floor has been requested
bool check_load_on_floor() 
{
    if(is_button_active_on_floor(floor_indicator)) 
    {
        set_state(STOP_AND_LOAD);
        return true;
    }
    return false;
}

// Sets direction and state to MOVING if activity_listener is set to either
// DIRN_DOWN or DIRN_UP
bool check_moving()
{
        elev_motor_direction_t activity_listener = get_request_direction(floor_indicator, prev_direction);
        if(activity_listener == DIRN_DOWN) 
        {
            set_motor_direction(DIRN_DOWN);
            set_state(MOVING);
            return true;
        }
        else if(activity_listener == DIRN_UP) 
        {
            set_motor_direction(DIRN_UP);
            set_state(MOVING);
            return true;
        }
        return false;
}

// Sets state to EMERGENCY_STOP_FLOOR if emergency button is pushed on a floor
// or EMERGENCY_STOP_B_FLOOR if it is pushed between a floor 
bool check_emergency()
{
    if(elev_get_floor_sensor_signal() != -1 && elev_get_stop_signal())
    {
        set_state(EMERGENCY_STOP_FLOOR);
        return true;
    }
    else if(elev_get_stop_signal())
    {
        set_state(EMERGENCY_STOP_B_FLOOR);
        return true;
    }
    return false;
}

<<<<<<< HEAD
// Checks if emergency button is released. If so a timer is started and the
// state is set to WAIT_FOR_REQUEST and the door is closed or WAIT_FOR_REQUEST_B_FLOOR 
// after the timer is up
bool check_button_released()
=======
bool  check_emergency_button_released()
>>>>>>> 31bd143da96358c10569563821b490537951c1c9
{
    if (!elev_get_stop_signal())
    {
        if (emergency_is_pressed)
        {
            emergency_is_pressed = false;
            start_timer(&timer, 3);
        }
        if (time_is_up(&timer))
        {
            if(get_state() == EMERGENCY_STOP_B_FLOOR) 
            {
                set_state(WAIT_FOR_REQUEST_B_FLOOR);
            }
            else 
            {
                elev_set_door_open_lamp(0);
                set_state(WAIT_FOR_REQUEST);
            }
            return true;
        }
    }
    if (elev_get_stop_signal())
    {
        emergency_is_pressed = true;
    }
    return false;
}

// Sets the motor direction and updates which direction it previously had 
void set_motor_direction(elev_motor_direction_t direction) 
{
    if(direction != DIRN_STOP) 
    {
	   prev_direction = direction;
    }
	elev_set_motor_direction(direction);
}

// Updates floor indicator light to current floor if the elevator reaches a new
// floor and is not between floors
void update_floor_indicator_light() 
{
    if(floor_indicator != elev_get_floor_sensor_signal() && elev_get_floor_sensor_signal() != -1) 
    {
        floor_indicator = elev_get_floor_sensor_signal();
        elev_set_floor_indicator(floor_indicator);
    }
}

