#ifndef DOOR_H
#define DOOR_H

#include "elev.h"
#include "utilities.h"

typedef struct door
{
	bool open;
} Door; 

void open_door();

void close_door();

#endif
