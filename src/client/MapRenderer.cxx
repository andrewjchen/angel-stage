#include "MapRenderer.hxx"

MapRenderer::MapRenderer(void *_map)
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
	for(int y = yoff; y < 32; y++)
	{
		for(int x = xoff; x < 32; x++)
		{
			char *a = (char*)(map);
			ALLEGRO_BITMAP *b = tiles[a[y*32+x]];
			if(b)
				al_draw_bitmap(b, (x - xoff) * TILE_WIDTH, (y - yoff) * TILE_HEIGHT, 0);
		}
	}
}

void MapRenderer::load_tiles()
{
	tiles[TILE_TYPE_NOTHING] = 0;
	tiles[TILE_TYPE_GRASS] = al_load_bitmap("res/tiles/grass.png");
}
