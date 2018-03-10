#include "timer.h"

Timer _timer;

double get_wall_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec* .000001;
}

void start_timer(double duration)
{
    _timer.start_time = get_wall_time();
    _timer.duration = duration;
}

double get_time_left()
{
    return (_timer.start_time + _timer.duration) - get_wall_time(); 
}

void reset_timer()
{
    _timer.start_time = get_wall_time(); 
}

bool time_is_up()
{
	return get_time_left() <= 0;
}
