#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include "elev.h"
#include "utilities.h"
#include "timer.h"
#include "buttons_handler.h"
#include "stop_button.h"
#include "motor.h"
#include "door.h"
#include "floor_indicator.h"

#include <stdio.h>

// The different states of the system
typedef enum elevator_state
{
	MOVING, //Elevator moving between floors
	STOP_AND_LOAD, //Elevator is on a floor and door is open for passangers
	WAIT_FOR_REQUEST, //Elevator is waiting for requests while on a floor
	WAIT_FOR_REQUEST_B_FLOOR, //Elevator is waiting for request between floor
	EMERGENCY_STOP_FLOOR, //Elevator is in emergency state on a floor
	EMERGENCY_STOP_B_FLOOR, //Elevator is in emergency state between floor
	INIT //Elevator do not know where it is and moves to find known location
} elevator_state_t;

// Updates sensors and change state if sensors triggerd
void update_event();

//Sets a new state and init the new state
void set_state(elevator_state_t elevator_state); 

//Return enum with state
elevator_state_t get_state();

#endif
