struct timer
{
    double start_time;
    double duration;
};

typedef struct timer timer;

// Return number of seconds after 1970
double get_wall_time(void);

void start_timer(timer tim, double duration);

// Checks if timer duration is done
double get_time_left(timer tim);

void reset_timer(timer tim);
