
int _activate;
elev_button_type_t _button_type;
int _floor;


void init(elev_button_type button_type, int floor) {
	_button_type = button_type;
	_floor = floor;
}