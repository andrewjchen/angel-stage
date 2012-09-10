#ifndef _POSITION_H_
#define _POSITION_H_

typedef double coordinate_t;

class Position {
private:
  coordinate_t _x, _y;

public:
  virtual coordinate_t getX();
  virtual coordinate_t getY();
  virtual coordinate_t setX(coordinate_t x);
  virtual coordinate_t setY(coordinate_t y);
}

#endif /* _POSITION_H_ */
