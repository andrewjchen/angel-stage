#include "Renderer.hxx"
#include "Debug.hxx"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

void Renderer::render() {
	al_clear_to_color(al_map_rgb(0,0,0));
	if (_map_renderer) {
		_map_renderer->render(_viewpoint.getX() / 16.0, _viewpoint.getY() / 16.0);
	}
	std::vector<VisualComponent *>::iterator iter;
	for (iter = _unit_layer.begin(); iter < _unit_layer.end(); iter++) {
		(*iter)->render(_viewpoint);
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
	DEBUG("adding visual component to Unit layer.\n");
	_unit_layer.push_back(visual_comp);
}

void Renderer::addMap(Map * map) {
	if (_map_renderer) {
		DEBUG("Trying to add multiple maps to one renderer!");
	} else {
		_map_renderer = new MapRenderer(map);
	}
}
