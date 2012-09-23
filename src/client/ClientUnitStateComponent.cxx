#include "ClientUnitStateComponent.hxx"
#include "ClientGameState.hxx"
#include "Entity.hxx"
#include <math.h>
#include "Debug.hxx"


ClientUnitStateComponent::ClientUnitStateComponent(ClientEntity* entity) : ClientComponent(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
}

void ClientUnitStateComponent::feedback(UnitFeedbackEvent* event) {
	_pos.setX(event->x);
	_pos.setY(event->y);
	_theta = event->theta;
}

const Position & ClientUnitStateComponent::getPosition() {
	return _pos;
}
