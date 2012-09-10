typedef double coordinate_t;

class Position {
private:
  coordinate_t x, y;

public:
  virtual getX();
  virtual getY();
  virtual setX(coordinate_t x);
  virtual setY(coordinate_t y);
}
