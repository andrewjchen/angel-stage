#include "UnitStateComponent.hxx"
#include "GameState.hxx"
#include "Entity.hxx"
#include <math.h>
#include "Debug.hxx"


UnitStateComponent::UnitStateComponent(Entity* entity) : Component(entity) {
	// entity->get_gamestate()->addClockListener(this);
	// DEBUG("Added unit state component");
}

const Position & UnitStateComponent::getPosition() {
	return _pos;
}
