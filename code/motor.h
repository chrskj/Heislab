#ifndef MOTOR_H
#define MOTOR_H

#include "elev.h"
#include "utilities.h"

typedef struct motor
{
	elev_motor_direction_t _current_direction;
	elev_motor_direction_t _prev_direction;
} Motor; 

//Sets up the motor with DIRN_STOP as direction
void motor_init();

//Sets the direction of the motor and saves the previous direction which is not DIRN_STOP
void motor_set_direction(elev_motor_direction_t dirn);

//Returns current direction
elev_motor_direction_t motor_get_current_direction();

//Returns previous direction
elev_motor_direction_t motor_get_prev_direction();

#endif
