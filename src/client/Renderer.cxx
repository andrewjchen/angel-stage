#include "Renderer.hxx"
#include "Debug.hxx"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void Renderer::render() {
	al_clear_to_color(al_map_rgb(0,0,0));
	if (_map_renderer) {
		_map_renderer->render(_viewpoint.getX(), _viewpoint.getY());
	}
	std::vector<VisualComponent *>::iterator iter;
	for (iter = _unit_layer.begin(); iter < _unit_layer.end(); iter++) {
		(*iter)->render(_viewpoint);
	}
	if (_select_rect_start != _select_rect_end) {
		Position screen1 = screenFromGame(_viewpoint, _select_rect_start);
		Position screen2 = screenFromGame(_viewpoint, _select_rect_end);
		double x1 = screen1.getX();
		double x2 = screen2.getX();
		double y1 = screen1.getY();
		double y2 =  screen2.getY();
		ALLEGRO_COLOR color = al_map_rgb(0xFF, 0xFF, 0xFF);
		al_draw_rounded_rectangle(x1, y1, x2, y2, 2, 2, color, 2);
	}
	al_flip_display();
}

void Renderer::setViewpoint(coordinate_t x, coordinate_t y) {
	_viewpoint.setX(x);
	_viewpoint.setY(y);
}

const Position & Renderer::getViewpoint() {
	return _viewpoint;
}

void Renderer::addToUnitLayer(VisualComponent * visual_comp) {
	DEBUG("adding visual component to Unit layer.");
	_unit_layer.push_back(visual_comp);
}

void Renderer::removeFromUnitLayer(VisualComponent* visual_comp) {
	DEBUG("removing visual component from Unit layer.");
	std::vector<VisualComponent*>::iterator it;
	for(it = _unit_layer.begin(); it != _unit_layer.end(); it++){
		if(*it == visual_comp) {
			_unit_layer.erase(it);
			return;
		}
	}

}

Renderer::~Renderer()
{
	if(_map_renderer) delete _map_renderer;
}

void Renderer::addMap(Map * map) {
	if (_map_renderer) {
		DEBUG("Trying to add multiple maps to one renderer!");
	} else {
		_map_renderer = new MapRenderer(map);
	}
}


void Renderer::setSelectionRectStart(Position start) {
	_select_rect_start = start;
}
void Renderer::setSelectionRectEnd(Position end) {
	_select_rect_end = end;
}
