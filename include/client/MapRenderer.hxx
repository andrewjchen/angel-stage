#ifndef MAPRENDER_H
#define MAPRENDER_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#define TILE_WIDTH		16
#define TILE_HEIGHT		16

#define TILE_TYPE_NOTHING	0
#define TILE_TYPE_GRASS		1
#define TILE_TYPE_MAX		2

class MapRenderer
{
public:
	MapRenderer(void *_map);
	~MapRenderer();
	void render(int xoff = 0, int yoff = 0);

private:
	void *map;
	ALLEGRO_BITMAP *tiles[TILE_TYPE_MAX];
	void load_tiles();
};

#endif
