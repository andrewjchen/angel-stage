#include <iostream>
#include "MapRenderer.hxx"

MapRenderer::MapRenderer(Map *_map)
{
	map = _map;
	load_tiles();
}

MapRenderer::~MapRenderer()
{
	for(int i = 0; i < TILE_TYPE_MAX; i++)
	{
		if(tiles[i])
			al_destroy_bitmap(tiles[i]);
	}
}

void MapRenderer::render(int xoff, int yoff)
{
	int xto = xoff + SCREEN_WIDTH;
	int yto = yoff + SCREEN_HEIGHT;
	
	if(xto > map->width()) xto = map->width();
	if(yto > map->height()) yto = map->height();

	for(int y = yoff; y < yto; y++)
	{
		for(int x = xoff; x < xto; x++)
		{
			ALLEGRO_BITMAP *b = tiles[(*map)[y*map->width()+x]];
			if(b)
				al_draw_bitmap(b, (x - xoff) * TILE_WIDTH, (y - yoff) * TILE_HEIGHT, 0);
		}
	}
}

void MapRenderer::load_tiles()
{
	tiles[TILE_TYPE_NOTHING] = 0;
	tiles[TILE_TYPE_GRASS] = al_load_bitmap("res/tiles/grass.png");
	tiles[TILE_TYPE_WALL] = al_load_bitmap("res/tiles/wall.png");
}
