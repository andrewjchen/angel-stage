#include "UnitVisualComponent.hxx"
#include "ClientEntity.hxx"
#include "RenderSetup.hxx"
#include "Debug.hxx"
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
	Position relative = this->_entity->get_unit_state_component()->getPosition().relative( viewpoint);
	double x = relative.getX() * 16.0;
	double y = relative.getY() * 16.0;
	if (x - (_half_bitmap_width * 16.0 / 512.0)  < display_width  &&
		y - (_half_bitmap_height * 16.0 / 512.0) < display_height &&
		x + (_half_bitmap_width * 16.0 / 512.0)  > 0 &&
		y + (_half_bitmap_height * 16.0 / 512.0) > 0 &&
		_bitmap) {
		/*al_draw_bitmap(_bitmap,
					   x - _half_bitmap_width,
					   y - _half_bitmap_height,
					   0);*/
		al_draw_tinted_scaled_rotated_bitmap(
			_bitmap, 
			al_map_rgb(255,0,0), 
			256, 
			256, 
			x - (_half_bitmap_width * 16.0 / 512.0), 
			y - (_half_bitmap_height * 16.0 / 512.0), 
			16.0 / 512.0, 16.0 / 512.0, 
			-this->_entity->get_unit_state_component()->getTheta(), 
			0);
	}
}
