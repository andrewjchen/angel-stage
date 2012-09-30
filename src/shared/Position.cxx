#include "math.h"
#include "Position.hxx"

void Position::init(const coordinate_t & x, const coordinate_t & y) {
	_x = x;
	_y = y;
}

coordinate_t Position::getX() const {
	return _x;
}

coordinate_t Position::getY() const {
	return _y;
}

coordinate_t Position::setX(const coordinate_t & x) {
	_x = x;
	return x;
}

coordinate_t Position::setY(const coordinate_t & y) {
	_y = y;
	return y;
}

Position Position::relative(const Position & origin) const {
	return Position(_x - origin.getX(), _y - origin.getY());
}

bool Position::within(const coordinate_t & w, const coordinate_t & h) const {
	return (0 <= _x && _x < w) && (0 <= _y && _y < h);
}

coordinate_t Position::distance(const Position & other) const {
	coordinate_t x_diff = fabs(other.getX() - _x);
	coordinate_t y_diff = fabs(other.getY() - _y);
	return sqrt(x_diff * x_diff + y_diff * y_diff);
}


Position screenFromGame(const Position & viewpoint,
						const Position & game_pos) {
	return Position(game_pos.getX() - viewpoint.getX(),
					game_pos.getY() - viewpoint.getY());
}

Position gameFromScreen(const Position & viewpoint,
						const Position & screen_pos) {
	return Position(viewpoint.getX() + screen_pos.getX(),
					viewpoint.getY() + screen_pos.getY());
}

bool Position::in_rect(const Position & top_left,
					   const Position & bottom_right) const {
	return (top_left.getX()     < _x &&
			bottom_right.getX() > _x &&
			top_left.getY()     > _y &&
			bottom_right.getY() < _y);
}
