#include "Pose.hxx"

Pose::Pose(ServerEntity* entity): ServerComponent(entity) {

}

Pose::~Pose() {

}

void Pose::tick(double wallTime, double deltaT) {
	//no action
}

const Position& Pose::get_position() {
	return _pos;
}

void Pose::set_position(Position pos) {
	_pos = pos;
}


double Pose::get_orientation() {
	return _theta;
}

void Pose::set_orientation(double orientation) {
	_theta = orientation;
}
