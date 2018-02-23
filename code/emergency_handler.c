#include "emergency.h"

//todo
// Remove all requests
// close door after three seconds on button release
// create set_state function

void update_emergency()
{
    if (elev_get_stop_signal() && elev_get_floor_sensor_signal() == -1)
    {
        emergency_between_floor();
    }
    if (elev_get_stop_signal() && elev_get_floor_sensor_signal() > -1)
    {
        emergency_on_floor();
    }
}

// Transition to state between floors
void emergency_between_floor()
{
    elev_set_door_open(0);
    set_motor_direction(DIRN_STOP);
    set_state(EMERGENCY_STOP_B_FLOOR);
    
}

// Transition to state on floor
void emergency_on_floor()
{
    elev_set_door_open(1);
    set_motor_direction(DIRN_STOP);
    set_state(EMERGENCY_STOP_FLOOR);
}
