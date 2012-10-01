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
	Renderer(Client * client) :
		_map_renderer(NULL),
		_client(client)
		{};
	virtual ~Renderer();
	virtual void render();
	virtual void setViewpoint(coordinate_t x, coordinate_t y);
	virtual const Position & getViewpoint();
	virtual void addToUnitLayer(Renderable * visual_comp);
	virtual void removeFromUnitLayer(Renderable* visual_comp);
	virtual void addMap(Map * map);
	virtual void setSelectionRectStart(Position start);
	virtual void setSelectionRectEnd(Position end);

private:
	Position _viewpoint;
	std::vector<Renderable *> _unit_layer;
	MapRenderer * _map_renderer;
	Position _select_rect_start;
	Position _select_rect_end;
	Client * _client;
};

#endif /* _RENDERER_HXX_ */
