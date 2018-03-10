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

void stop_set_active();

void stop_set_inactive();

void stop_button_update();

bool stop_is_active();

#endif
