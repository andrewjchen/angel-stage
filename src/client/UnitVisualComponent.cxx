#include "UnitVisualComponent.hxx"
#include "ClientEntity.hxx"
#include "RenderSetup.hxx"
#include "Debug.hxx"
#include "Position.hxx"
#include <math.h>


UnitVisualComponent::UnitVisualComponent(ClientEntity * entity) : VisualComponent(entity) {
	_bitmap = al_load_bitmap("res/unit.png");
	if (!_bitmap) {
		DEBUG("Bitmap res/unit.png could not be loaded!\n");
	}
	_half_bitmap_width  = ceil((double) al_get_bitmap_width(_bitmap) / 2);
	_half_bitmap_height = ceil((double) al_get_bitmap_height(_bitmap) / 2);
}

void UnitVisualComponent::tick(double wallTime, double deltaT) {
	
}

void UnitVisualComponent::render(const Position & viewpoint) {
	Position screen_pos = screenFromGame(viewpoint, _entity->get_unit_state_component()->getPosition());
	double screenX = screen_pos.getX();
	double screenY = screen_pos.getY();
	double scale = 16.0 / 512.0;
	if (screenX - _half_bitmap_width < display_width &&
		screenY - _half_bitmap_height < display_height &&
		screenX + _half_bitmap_width > 0 &&
		screenY + _half_bitmap_width > 0 &&
		_bitmap) {
		al_draw_tinted_scaled_rotated_bitmap(
			_bitmap,
			al_map_rgb(255, 0, 255),
			_half_bitmap_width,
			_half_bitmap_height,
			screenX,
			screenY,
			scale,
			scale,
			-_entity->get_unit_state_component()->getTheta(),
			0
			);
	}
}
