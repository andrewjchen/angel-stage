#include "Size.hxx"

Size::Size(ServerEntity* entity) : ServerComponent(entity) {

}

Size::~Size() {

}

void Size::tick(double wallTime, double deltaT) {
	//no action
}

double Size::get_size() {
	return _size;
}

void Size::set_size(double size) {
	_size = size;
}