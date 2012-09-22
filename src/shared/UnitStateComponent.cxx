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
	_x = event->x;
	_y = event->y;
	_theta = event->theta;
}

void UnitStateComponent::tick(double wallTime, double deltaT) {
	DEBUG(wallTime);
	_x = 500 * sin(wallTime) + 500;
	_y = 500 * cos(wallTime) + 500;
}
