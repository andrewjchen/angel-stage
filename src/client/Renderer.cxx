#include "Renderer.hxx"
#include "Debug.hxx"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void Renderer::render() {
    al_clear_to_color(al_map_rgb(0,0,0));
    if (_map_renderer) {
        _map_renderer->render(_viewpoint.get_x(), _viewpoint.get_y(), _client);
    }
    std::vector<Renderable *>::iterator iter;
    for (iter = _unit_layer.begin(); iter < _unit_layer.end(); iter++) {
        (*iter)->render(_viewpoint, _client);
    }
    if (_select_rect_start != _select_rect_end) {
        Position screen1 = screenFromGame(_viewpoint, _select_rect_start);
        Position screen2 = screenFromGame(_viewpoint, _select_rect_end);
        double x1 = screen1.get_x();
        double x2 = screen2.get_x();
        double y1 = screen1.get_y();
        double y2 =  screen2.get_y();
        ALLEGRO_COLOR color = al_map_rgb(0xFF, 0xFF, 0xFF);
        al_draw_rounded_rectangle(x1, y1, x2, y2, 2, 2, color, 2);
    }
    al_flip_display();
}

void Renderer::set_viewpoint(coordinate_t x, coordinate_t y) {
    _viewpoint.set_x(x);
    _viewpoint.set_y(y);
}

const Position &Renderer::get_viewpoint() {
    return _viewpoint;
}

void Renderer::add_to_unit_layer(Renderable *visual_comp) {
    DEBUG("adding visual component to Unit layer.");
    _unit_layer.push_back(visual_comp);
}

void Renderer::remove_from_unit_layer(Renderable *visual_comp) {
    DEBUG("removing visual component from Unit layer.");
    std::vector<Renderable *>::iterator it;
    for(it = _unit_layer.begin(); it != _unit_layer.end(); it++) {
        if(*it == visual_comp) {
            _unit_layer.erase(it);
            return;
        }
    }

}

void Renderer::add_map(Map *map) {
    if (_map_renderer) {
        DEBUG("Trying to add multiple maps to one renderer!");
    } else {
        _map_renderer = new MapRenderer(map);
    }
}


void Renderer::set_selection_rect_start(Position start) {
    _select_rect_start = start;
}
void Renderer::set_selection_rect_end(Position end) {
    _select_rect_end = end;
}

Renderer::~Renderer() {
    if (_map_renderer) {
        delete _map_renderer;
    }
}
