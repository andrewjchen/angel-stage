#ifndef _UNIT_STATE_COMPONENT_HXX_
#define _UNIT_STATE_COMPONENT_HXX_

#include "Component.hxx"
#include "EventTypes.hxx"
#include "Position.hxx"

class UnitStateComponent : public Component {

public:
	UnitStateComponent(Entity* entity);
	virtual ~UnitStateComponent() {};
	virtual const Position & getPosition();

protected:
	Position _pos;
	double _theta;
};

#endif
