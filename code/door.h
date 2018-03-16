#ifndef DOOR_H
#define DOOR_H

#include "elev.h"
#include "utilities.h"

typedef struct door
{
	bool open;
} Door; 

//Opens the door
void open_door();

//Closes the door
void close_door();

#endif
