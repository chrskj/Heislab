#ifndef MOTOR_H
#define MOTOR_H

#include "elev.h"
#include "utilities.h"

typedef struct motor
{
	elev_motor_direction_t _current_direction;
	elev_motor_direction_t _prev_direction;
} Motor; 

void motor_init();

void motor_set_direction(elev_motor_direction_t dirn);

elev_motor_direction_t motor_get_current_direction();

elev_motor_direction_t motor_get_prev_direction();

#endif