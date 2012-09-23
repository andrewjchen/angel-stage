#include "ServerUnitStateComponent.hxx"
#include "ServerGameState.hxx"
#include "ServerEntity.hxx"
#include <math.h>
#include "Debug.hxx"


ServerUnitStateComponent::ServerUnitStateComponent(ServerEntity* entity) : ServerComponent(entity) {
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
