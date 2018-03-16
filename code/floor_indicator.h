#ifndef FLOOR_INDICATOR_H
#define FLOOR_INDICATOR_H

#include "elev.h"
#include "utilities.h"
#include "motor.h"

typedef struct floor_indicator
{
	int _floor;
	float _precise_floor;
	bool stopped_at_floor;
	elev_motor_direction_t _floor_exit_dir;
} Floor_indicator; 

void update_precise_floor_indicator();

float get_precise_floor();

//update light that indicates current floor
void update_floor_indicator();

int get_floor();

void set_stopped_at_floor(bool decision);

bool get_stopped_at_floor();

#endif
