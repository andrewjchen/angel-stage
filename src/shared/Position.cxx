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
