#include "elev.h"

struct button {
	int _active;
	elev_button_type_t _button_type;
	int _floor;
}; 
typedef struct button button;

void button_init(button * self, elev_button_type_t button_type, int floor);
void button_set_active(button * self);
void button_set_inactive(button * self);
int button_get_floor(button * self);
elev_button_type_t button_get_type(button * self);