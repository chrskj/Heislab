#ifndef BUTTONS_HANDLER_H
#define BUTTONS_HANDLER_H

#include <stdio.h>

#include "elev.h"
#include "button.h"
#include "utilities.h"
#include "state_machine.h"

void buttons_handler_init();
void buttons_handler_update();
void turn_buttons_on_floor_off(int floor);
elev_motor_direction_t get_request_direction(int floor, elev_motor_direction_t direction);
bool to_stop_on_floor(int floor, elev_motor_direction_t direction);
bool is_button_active_on_floor(int floor); 

#endif
