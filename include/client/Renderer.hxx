#ifndef _RENDERER_HXX_
#define _RENDERER_HXX_

#include "Position.hxx"
#include "Renderable.hxx"
#include "MapRenderer.hxx"
#include <allegro5/allegro_primitives.h>

#include <vector>

struct Client;

class Renderer {
public:
    Renderer(Client *client) :
        _map_renderer(NULL),
        _client(client)
    {};
    virtual ~Renderer();
    virtual void render();
    virtual void set_viewpoint(coordinate_t x, coordinate_t y);
    virtual const Position &get_viewpoint();
    virtual void add_to_unit_layer(Renderable *visual_comp);
    virtual void remove_from_unit_layer(Renderable *visual_comp);
    virtual void add_map(Map *map);
    virtual void set_selection_rect_start(Position start);
    virtual void set_selection_rect_end(Position end);

private:
    Position _viewpoint;
    std::vector<Renderable *> _unit_layer;
    MapRenderer *_map_renderer;
    Position _select_rect_start;
    Position _select_rect_end;
    Client *_client;
};

#endif /* _RENDERER_HXX_ */
