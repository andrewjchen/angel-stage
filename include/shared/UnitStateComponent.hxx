#ifndef UNIT_STATE_COMPONENT_H
#define UNIT_STATE_COMPONENT_H

#include "Component.hxx"
//#include "Event.hxx"
#include "EventTypes.hxx"

class UnitStateComponent: public Component {

public:
	UnitStateComponent(Entity* entity);//: Component(entity) {} ;
	~UnitStateComponent() {};

	virtual void tick(double wallTime, double deltaT);


	virtual void feedback(UnitFeedbackEvent* event);
private:
	double _x;
	double _y;
	double _theta;
};

#endif
