#include "elev.h"
#include "button.h"
#include <stdio.h>
#include "utilities.h"

void buttons_handler_init();
void buttons_handler_update();
void turn_buttons_on_floor_off(int floor);
elev_motor_direction_t prefered_direction(int floor, bool direction); 