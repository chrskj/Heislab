#ifndef BUTTON_H
#define BUTTON_H

#include "elev.h"
#include "utilities.h"

typedef struct button
{
	int _active;
	elev_button_type_t _button_type;
	int _floor;
} Button; 

void button_init(Button* self, elev_button_type_t button_type, int floor);
void button_set_active(Button* self);
void button_set_inactive(Button* self);
int button_get_floor(Button* self);
bool button_is_active(Button* self);
elev_button_type_t button_get_type(Button* self);

#endif
