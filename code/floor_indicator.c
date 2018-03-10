#include "floor_indicator.h"

Floor_indicator _floor_indicator;

// Returns which floors the elevator is on more precisely
// 0.5 is in between 0 and 1
// 1.5 is in between 1 and 2
// 2.5 is in between 2 and 3
void update_precise_floor_indicator()
{
	if (elev_get_floor_sensor_signal() != -1)
	{
		_floor_indicator._floor_exit_dir = motor_get_current_direction();
		_floor_indicator._precise_floor = _floor_indicator._floor;
	}	
	else
	{
		float modifier = 0;
		if (_floor_indicator._floor_exit_dir == DIRN_UP)
		{
			modifier = 0.5;
		}
		else if (_floor_indicator._floor_exit_dir == DIRN_DOWN)
		{
			modifier = -0.5;
		}
		_floor_indicator._precise_floor = _floor_indicator._floor + modifier;
	}
}

float get_precise_floor()
{
	return _floor_indicator._precise_floor;
}


//update light that indicates current floor
void update_floor_indicator() 
{
    //printf("%i != %i ?, %i != -1\n",  floor_indicator, elev_get_floor_sensor_signal(), elev_get_floor_sensor_signal());
    if(_floor_indicator._floor != elev_get_floor_sensor_signal() && elev_get_floor_sensor_signal() != -1) 
    {
        _floor_indicator._floor = elev_get_floor_sensor_signal();
        elev_set_floor_indicator(_floor_indicator._floor);
    }
}

int get_floor()
{
	return _floor_indicator._floor;
}

void set_stopped_at_floor(bool decision)
{
	_floor_indicator.stopped_at_floor = decision;
}

bool get_stopped_at_floor()
{
	return _floor_indicator.stopped_at_floor;
}