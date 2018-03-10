#include "door.h"

Door _door;

void open_door()
{
	elev_set_door_open_lamp(1);
}

void close_door()
{
	elev_set_door_open_lamp(0);
}