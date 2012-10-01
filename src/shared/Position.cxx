#include "math.h"
#include "Position.hxx"

void Position::init(const coordinate_t & x, const coordinate_t & y) {
	_x = x;
	_y = y;
}

coordinate_t Position::get_x() const {
	return _x;
}

coordinate_t Position::get_y() const {
	return _y;
}

coordinate_t Position::set_x(const coordinate_t & x) {
	_x = x;
	return x;
}

coordinate_t Position::set_y(const coordinate_t & y) {
	_y = y;
	return y;
}

Position Position::relative(const Position & origin) const {
	return Position(_x - origin.get_x(), _y - origin.get_y());
}

bool Position::within(const coordinate_t & w, const coordinate_t & h) const {
	return (0 <= _x && _x < w) && (0 <= _y && _y < h);
}

coordinate_t Position::distance(const Position & other) const {
	coordinate_t x_diff = fabs(other.get_x() - _x);
	coordinate_t y_diff = fabs(other.get_y() - _y);
	return sqrt(x_diff * x_diff + y_diff * y_diff);
}


Position screenFromGame(const Position & viewpoint,
						const Position & game_pos) {
	return Position(game_pos.get_x() - viewpoint.get_x(),
					game_pos.get_y() - viewpoint.get_y());
}

Position gameFromScreen(const Position & viewpoint,
						const Position & screen_pos) {
	return Position(viewpoint.get_x() + screen_pos.get_x(),
					viewpoint.get_y() + screen_pos.get_y());
}

bool Position::in_rect(const Position & top_left,
					   const Position & bottom_right) const {
	return (top_left.get_x()     < _x &&
			bottom_right.get_x() > _x &&
			top_left.get_y()     > _y &&
			bottom_right.get_y() < _y);
}
