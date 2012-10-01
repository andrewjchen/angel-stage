#ifndef MAPRENDER_H
#define MAPRENDER_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "Map.hxx"

#define TILE_WIDTH    16
#define TILE_HEIGHT   16

struct Client;

class MapRenderer
{
public:
	MapRenderer(Map *_map);
	~MapRenderer();
	void render(int xoff, int yoff, Client * client);

private:
	Map *map;
	ALLEGRO_BITMAP *tiles[TILE_TYPE_MAX];
	void load_tiles();
};

#endif
