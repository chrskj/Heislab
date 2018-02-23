#include "elev.h"
#include <stdio.h>
#include "utilities.h"
#include "timer.h"
#include "buttons_handler.h"

enum elevator_state{
	MOVING,
	STOP_AND_LOAD,
	IDLE,
	EMERGENCY_STOP_FLOOR,
	EMERGENCY_STOP_B_FLOOR
}; 
typedef enum elevator_state elevator_state_t;

//typedef enum elevator_state elevator_state;
//elevator_state state;

void update_state(); 