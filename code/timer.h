#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <sys/time.h>

#include "utilities.h"

struct timer
{
    double start_time;
    double duration;
};

typedef struct timer Timer;

// Return number of seconds after 1970
double get_wall_time(void);

void start_timer(Timer* tim, double duration);

// Checks if timer duration is done
double get_time_left(Timer * tim);

void reset_timer(Timer* tim);


bool time_is_up(Timer* tim);

#endif