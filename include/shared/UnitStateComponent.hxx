#ifndef UNIT_STATE_COMPONENT_H
#define UNIT_STATE_COMPONENT_H

#include "Component.hxx"

class UnitStateComponent: public Component {

public:
	UnitStateComponent(Entity* entity);//: Component(entity) {} ;
	~UnitStateComponent() {};

//	void update(); //TODO

	virtual void tick(double wallTime, double deltaT);


private:
	double x;
	double y; 
	double theta;

};

#endif