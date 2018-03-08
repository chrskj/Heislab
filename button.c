#include "button.h"

// Initializes a button with specified button type and floor 
void button_init(button* self, elev_button_type_t button_type, int floor) 
{
	self->_button_type = button_type;
	self->_floor = floor;
}

// Sets a button active and lights it up
void button_set_active(button* self) 
{
	self->_active = 1;
	elev_set_button_lamp(self->_button_type, self->_floor, 1);
}

// Sets a button inactive and turns the light off
void button_set_inactive(button* self) 
{
	self->_active = 0;
	elev_set_button_lamp(self->_button_type, self->_floor, 0);
}

// Returns the floor of a button
int button_get_floor(button* self)
{
	return self->_floor;
}

// Returns the button type of a button
elev_button_type_t button_get_type(button* self)
{
	return self->_button_type;
}

// Returns 1 if button is active and 0 if it is not
bool button_is_active(button* self)
{
	return self->_active;
}
