#include "motor.h"

Motor _motor;

void motor_init()
{
	_motor._current_direction = DIRN_STOP;
	_motor._prev_direction = DIRN_STOP;
}

//Sets the motor direction of the elevator
void motor_set_direction(elev_motor_direction_t dirn)
{
	if(motor_get_current_direction() != DIRN_STOP)
	{
		_motor._prev_direction = motor_get_current_direction();
	}
	_motor._current_direction = dirn;
	elev_set_motor_direction(dirn);
}

elev_motor_direction_t motor_get_current_direction()
{
	return _motor._current_direction;
}

elev_motor_direction_t motor_get_prev_direction()
{
	return _motor._prev_direction;
}
