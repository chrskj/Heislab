#ifndef BUTTONS_HANDLER_H
#define BUTTONS_HANDLER_H

#include <stdio.h>

#include "elev.h"
#include "button.h"
#include "utilities.h"
#include "elevator_controller.h"
#include "stop_button.h"

//Initialize all buttons 
void buttons_handler_init();

//Check if buttons is pressed and set their state to active if pressed
void buttons_handler_update();

//Sets all buttons on floor inactive
void turn_buttons_on_floor_off(int floor);

//When leaving floor find the preferd direction by looking at active buttons
elev_motor_direction_t get_request_direction(int floor, elev_motor_direction_t direction);

//Determine if elevator should stop at floor
bool to_stop_on_floor(int floor, elev_motor_direction_t direction);

//Determine if any button is active on floor
bool is_button_active_on_floor(int floor); 

//Sets all buttons inactive
void remove_all_requests();

//Find the preferd direction after emegency to return to requested floor
elev_motor_direction_t find_direction_after_emergency(int current_floor, int desired_floor, elev_motor_direction_t prev_direction);

//Return the index of the the first floor where there is an active button
int get_first_active_floor();
 
#endif
