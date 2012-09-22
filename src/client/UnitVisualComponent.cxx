#include "UnitVisualComponent.hxx"
#include "Entity.hxx"
#include "RenderSetup.hxx"
#include "Debug.hxx"


UnitVisualComponent::UnitVisualComponent(Entity * entity) : VisualComponent(entity) {
	_bitmap = al_load_bitmap("res/unit.png");
	if (!_bitmap) {
		DEBUG("Bitmap res/unit.png could not be loaded!\n");
	}
	_bitmap_width = al_get_bitmap_width(_bitmap);
	_bitmap_height = al_get_bitmap_height(_bitmap);
}

void UnitVisualComponent::tick(double wallTime, double deltaT) {
}

void UnitVisualComponent::render(const Position & viewpoint) {
	Position relative = this->_entity->get_unit_state_component()->getPosition().relative( viewpoint);
	if (relative.getX() < display_width - _bitmap_width &&
		relative.getY() < display_height - _bitmap_height &&
		relative.getX() > 0 && relative.getY() > 0 &&
		_bitmap) {
		al_draw_bitmap(_bitmap, relative.getX(), relative.getY(), 0);
	}
}
