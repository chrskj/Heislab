#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <sys/time.h>

#include "utilities.h"

typedef struct timer
{
    double start_time;
    double duration;
} Timer;

//Return number of seconds after 1970
double get_wall_time(void);

//Starts timer with desired duration and start_time
void start_timer(double duration);

//Returns how much time is left
double get_time_left();

//Sets new start time and keeps same duration
void reset_timer();

//Returns true if time is up
bool time_is_up();

#endif
