#include "UnitStateComponent.hxx"
#include "GameState.hxx"
#include "Entity.hxx"
#include <math.h>
#include "Debug.hxx"


UnitStateComponent::UnitStateComponent(Entity* entity) : Component(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
}

void UnitStateComponent::feedback(UnitFeedbackEvent* event) {
	_pos.setX(event->x);
	_pos.setY(event->y);
	_theta = event->theta;
}

void UnitStateComponent::tick(double wallTime, double deltaT){
	_pos.setX(500* sin(wallTime) + 500);
	_pos.setY(500* sin(wallTime) + 500);
}

const Position & UnitStateComponent::getPosition() {
	return _pos;
}
