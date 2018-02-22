#include "button.h"




void button_init(button * self, elev_button_type_t button_type, int floor) 
{
	self->_button_type = button_type;
	self->_floor = floor;
}

void button_set_active(button * self) 
{
	self->_active = 1;
}

void button_set_inactive(button * self) 
{
	self->_active = 0;
}

int button_get_floor(button * self)
{
	return self->_floor;
}
elev_button_type_t button_get_type(button * self) {
	return self->_button_type;
}