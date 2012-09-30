#ifndef _RENDERER_HXX_
#define _RENDERER_HXX_

#include "Position.hxx"
#include "VisualComponent.hxx"
#include "MapRenderer.hxx"
#include <allegro5/allegro_primitives.h>

#include <vector>

class Renderer {
public:
	Renderer() : _map_renderer(NULL) {};
	virtual ~Renderer() {};
	virtual void render();
	virtual void setViewpoint(coordinate_t x, coordinate_t y);
	virtual const Position & getViewpoint();
	virtual void addToUnitLayer(VisualComponent * visual_comp);
	virtual void addMap(Map * map);
	virtual void setSelectionRectStart(Position start);
	virtual void setSelectionRectEnd(Position end);
private:
	Position _viewpoint;
	std::vector<VisualComponent *> _unit_layer;
	MapRenderer * _map_renderer;
	Position _select_rect_start;
	Position _select_rect_end;
};

#endif /* _RENDERER_HXX_ */
