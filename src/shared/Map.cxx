#include "Map.hxx"

Map::Map(int _size)
{
	size = _size;
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
	int col = i % size;
	int row = i / size;
	
	if(col == 0 || row == 0 || col == (size - 1) || row == (size - 1))
		return TILE_TYPE_WALL;
	
	return TILE_TYPE_GRASS;
}
