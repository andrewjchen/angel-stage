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

void UnitStateComponent::update(){

}
*/

void UnitStateComponent::tick(double wallTime, double deltaT){


	DEBUG(wallTime);
	x = 500* sin(wallTime) + 500;
	y = 500* cos(wallTime) + 500;

}	
