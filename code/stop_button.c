#include "stop_button.h"

//Check if emergency button is pressed to enter EMERGENCY state

Stop_button _stop_button;

void stop_set_active()
{
    _stop_button._active = true;
    elev_set_stop_lamp(1);
    remove_all_requests();
}

void stop_set_inactive()
{
    _stop_button._active = false;
    elev_set_stop_lamp(0);
}

void stop_button_update()
{
    if(elev_get_stop_signal())
    {
        stop_set_active();
    }
    else
    {
        stop_set_inactive();
    }
}

bool stop_is_active()
{
    return _stop_button._active;
}