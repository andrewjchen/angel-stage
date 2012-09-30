#include <cstdlib>
#include "Map.hxx"

Map::Map(int _size, unsigned int prngseed)
{
	size = _size;
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
