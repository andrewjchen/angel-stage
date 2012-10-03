#include "Position.cxx"

int main(int argc, char *argv[]) {

    Position pos1;
    pos1.setX(1);
    pos1.setY(1);
    Position pos2(2.0, 2.0);
    Position pos3(-1, -1);
    if (pos3.getX() != pos1.relative(pos2).getX()) {
        return 1;
    }
    if (pos3.getY() != pos1.relative(pos2).getY()) {
        return 1;
    }
    return 0;
}
