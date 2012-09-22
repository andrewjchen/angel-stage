#ifndef MAP_H
#define MAP_H
#include <stdint.h>

#define TILE_TYPE_NOTHING   0
#define TILE_TYPE_GRASS     1
#define TILE_TYPE_WALL      2
#define TILE_TYPE_MAX       3

//currently, the map is a fixed 2048x2048 with no height
//the playable area is 2046x2046

//#define MAP_SIZE	2048

class Map
{
public:
	Map(int _size);
	int width();
	int height();
	const uint8_t &operator[](int i);

private:
	int size;
};

#endif
