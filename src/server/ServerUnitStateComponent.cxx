#include "ServerUnitStateComponent.hxx"
#include "ServerGameState.hxx"
#include "ServerEntity.hxx"
#include <math.h>
#include "Debug.hxx"

#include "EventTypes.hxx"

ServerUnitStateComponent::ServerUnitStateComponent(ServerEntity* entity) : ServerComponent(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
}

void ServerUnitStateComponent::tick(double wallTime, double deltaT){
	_pos.setX(500* sin(wallTime) + 500);
	_pos.setY(500* sin(wallTime) + 500);


	Event header;
	header.event_type = EVENT_UNIT_MOVE;
	header.total_byte_count = 10;

	EntityEvent entityEvent;
	entityEvent.header = header;
	entityEvent.entity_id = _entity->get_id();

	UnitFeedbackEvent event;
	event.header = entityEvent;
	event.x = _pos.getX();
	event.y = _pos.getY();
	event.theta = _theta;
	
}

const Position & ServerUnitStateComponent::getPosition() {
	return _pos;
}
