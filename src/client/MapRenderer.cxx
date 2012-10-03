#include <iostream>
#include "MapRenderer.hxx"
#include "Client.hxx"

MapRenderer::MapRenderer(Map *_map) {
    map = _map;
    load_tiles();
}

MapRenderer::~MapRenderer() {
    for(int i = 0; i < TILE_TYPE_MAX; i++) {
        if(tiles[i]) {
            al_destroy_bitmap(tiles[i]);
        }
    }
    if (map) {
        delete map;
    }
}

void MapRenderer::render(int xoff, int yoff, Client *client) {
    // int xtilefrom = xoff / 16;
// int ytilefrom = yoff / 16;
    // int xpartialtile = xoff % 16;
    // int ypartialtile = yoff % 16;
    // int xtileto = (xoff + client->display_width + 15) / 16;
    // int ytileto = (yoff + client->display_height + 15) / 16;

    // for(int y = ytilefrom; y < ytileto; y++) {
    //     for(int x = xtilefrom; x < xtileto; x++) {
    //         ALLEGRO_BITMAP *b = NULL;
    //         if(!(x < 0 || y < 0 || x >= map->width() || y >= map->height()))
    //             b = tiles[(*map)[y*map->width()+x]];
    //         if(b)
    //             al_draw_bitmap(b, (x - xtilefrom) * TILE_WIDTH - xpartialtile, (y - ytilefrom) * TILE_HEIGHT - ypartialtile, 0);
    //     }
    // }
}

void MapRenderer::load_tiles() {
    // tiles[TILE_TYPE_NOTHING] = 0;
    // tiles[TILE_TYPE_GRASS] = al_load_bitmap("res/tiles/grass.png");
    // tiles[TILE_TYPE_WALL] = al_load_bitmap("res/tiles/wall.png");
    // tiles[TILE_TYPE_MITHRIL] = al_load_bitmap("res/tiles/mithril.png");
}
