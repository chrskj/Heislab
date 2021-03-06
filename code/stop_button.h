#ifndef STOP_BUTTON_H
#define STOP_BUTTON_H

#include "elev.h"
#include "elevator_controller.h"
#include "timer.h"
#include "utilities.h"
#include "buttons_handler.h"

typedef struct stop_button
{
    int _active;
} Stop_button;

//Sets the stop button to active
void stop_set_active();

//Sets the stop button to inactive
void stop_set_inactive();

//Sets the stop button active is the button is pressed and inactive if it is not
void stop_button_update();

//Returns true if stop button is active
bool stop_is_active();

#endif
