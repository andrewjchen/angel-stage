#include "UnitVisualComponent.hxx"
#include "Entity.hxx"
#include "RenderSetup.hxx"
#include "Debug.hxx"
#include <math.h>


UnitVisualComponent::UnitVisualComponent(Entity * entity) : VisualComponent(entity) {
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
	if (relative.getX() - _half_bitmap_width  < display_width  &&
		relative.getY() - _half_bitmap_height < display_height &&
		relative.getX() + _half_bitmap_width  > 0 &&
		relative.getY() + _half_bitmap_height > 0 &&
		_bitmap) {
		al_draw_bitmap(_bitmap,
					   relative.getX() - _half_bitmap_width,
					   relative.getY() - _half_bitmap_height,
					   0);
	}
}
