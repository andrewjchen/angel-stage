#include "ServerUnitStateComponent.hxx"
#include "GameState.hxx"
#include "Entity.hxx"
#include <math.h>
#include "Debug.hxx"


ServerUnitStateComponent::ServerUnitStateComponent(Entity* entity) : UnitStateComponent(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
}

void ServerUnitStateComponent::tick(double wallTime, double deltaT){
	_pos.setX(500* sin(wallTime) + 500);
	_pos.setY(500* sin(wallTime) + 500);
}

const Position & ServerUnitStateComponent::getPosition() {
	return _pos;
}
