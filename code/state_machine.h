#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "elev.h"
#include <stdio.h>
#include "utilities.h"
#include "timer.h"
#include "buttons_handler.h"

enum elevator_state{
	MOVING,
	STOP_AND_LOAD,
	WAIT_FOR_REQUEST,
	WAIT_FOR_REQUEST_B_FLOOR,
	EMERGENCY_STOP_FLOOR,
	EMERGENCY_STOP_B_FLOOR,
	INIT
}; 
typedef enum elevator_state elevator_state_t;

//typedef enum elevator_state elevator_state;
//elevator_state state;

void update_event();

void set_state(elevator_state_t elevator_state); 

elevator_state_t get_state();

#endif
