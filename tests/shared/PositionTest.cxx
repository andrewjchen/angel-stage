#include "Position.cxx"

int main(int argc, char *argv[]) {
  Position pos1;
  pos1.set_x(1);
  pos1.set_y(1);
  Position pos2(2.0, 2.0);
  Position pos3(-1, -1);
  if (pos3.get_x() != pos1.relative(pos2).get_x()) {
    return 1;
  }
  if (pos3.get_y() != pos1.relative(pos2).get_y()) {
    return 1;
  }
  return 0;
}
