#include <cstdlib>
#include <string.h>
#include "Map.hxx"

Map::Map(int _size, unsigned int prngseed)
{
	size = _size;
	seed = prngseed;
	data = new uint8_t[size * size];
	srand(prngseed);
	for(int y = 0; y < size; y++)
	{
		for(int x = 0; x < size; x++)
		{
			if(x == 0 || y == 0 || x == (size - 1) || y == (size - 1))
				data[y*size+x] = TILE_TYPE_WALL;
			else if((((float)(rand())) / ((float)(RAND_MAX))) < 0.05)
				data[y*size+x] = TILE_TYPE_MITHRIL;
			else
				data[y*size+x] = TILE_TYPE_GRASS;
		}
	}
}

Map::~Map()
{
	if(data) delete[] data;
}

int Map::width()
{
	return size;
}

int Map::height()
{
	return size;
}
	
const uint8_t &Map::operator[](int i)
{
	return data[i];
}

uint8_t *Map::save(int *_size)
{
	uint8_t *buf = new uint8_t[size * size + sizeof(size)];
	*_size = size * size + sizeof(size);
	memcpy(buf, &size, sizeof(size));
	memcpy(buf + sizeof(size), data, size * size);
	
	return buf;
}

Map *Map::load(uint8_t *buf)
{
	int size = *((int*)(buf));
	return new Map(size, buf + sizeof(size));
}

Map::Map(int _size, uint8_t *stuff)
{
	size = _size;
	data = new uint8_t[size * size];
	memcpy(data, stuff, size * size);
}
