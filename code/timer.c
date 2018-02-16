#include <sys/time.h>
#include <stdio.h>
#include "timer.h"

timer tim;

double get_wall_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void start_timer(timer tim, double duration)
{
    tim.start_time = get_wall_time();
    tim.duration = duration;
}

double get_time_left(timer tim)
{
    return (tim.start_time + tim.duration) - get_wall_time(); 
}

void reset_timer(timer tim)
{
    tim.start_time = get_wall_time(); 
}

