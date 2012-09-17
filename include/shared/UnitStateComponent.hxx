#ifndef UNIT_STATE_COMPONENT_H
#define UNIT_STATE_COMPONENT_H

#include "Component.hxx"

class UnitStateComponent: public Component {

public:
	UnitStateComponent(Entity* Entity) : Component(entity) {};
	~UnitStateComponent() {};
	virtual feedback(UnitFeedbackEvent * event);
private:
	double _x;
	double _y;
	double _theta;
};

#endif
