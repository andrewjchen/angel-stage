#include "UnitStateComponent.hxx"
#include "GameState.hxx"
#include "Entity.hxx"
#include <math.h>
#include "Debug.hxx"


UnitStateComponent::UnitStateComponent(Entity* entity) : Component(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
}

/*

<<<<<<< HEAD
void UnitStateComponent::update(){

}
*/

void UnitStateComponent::tick(double wallTime, double deltaT){


	DEBUG(wallTime);
	x = 500* sin(wallTime) + 500;
	y = 500* cos(wallTime) + 500;

}	
=======
void UnitStateComponent::update(UnitFeedbackEvent * event) {
	_x = event->x;
	_y = event->y;
	_theta = event->theta;
}
>>>>>>> 9faf59d8985e7dd192bc490b6fb8c11953209d5b
