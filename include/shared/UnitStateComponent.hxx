#ifndef UNIT_STATE_COMPONENT_H
#define UNIT_STATE_COMPONENT_H

#include "Component.hxx"

class UnitStateComponent: public Component {

public:
	UnitStateComponent(Entity* Entity) : Component(entity) {};
	~UnitStateComponent() {};

	update(); //TODO


private:
	double x;
	double y; 
	double theta;



};

#endif