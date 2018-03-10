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

// Return number of seconds after 1970
double get_wall_time(void);

void start_timer(double duration);

// Checks if timer duration is done
double get_time_left();

void reset_timer();

bool time_is_up();

#endif
