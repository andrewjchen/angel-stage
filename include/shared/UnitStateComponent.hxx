#ifndef _UNIT_STATE_COMPONENT_HXX_
#define _UNIT_STATE_COMPONENT_HXX_

#include "Component.hxx"
#include "EventTypes.hxx"

class UnitStateComponent : public Component {

public:
	UnitStateComponent(Entity* entity);
	virtual ~UnitStateComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual void feedback(UnitFeedbackEvent* event);

private:
	double _x;
	double _y;
	double _theta;
};

#endif
