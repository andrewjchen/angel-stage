#ifndef _SERVER_UNIT_STATE_COMPONENT_HXX_
#define _SERVER_UNIT_STATE_COMPONENT_HXX_

#include "UnitStateComponent.hxx"

class ServerUnitStateComponent : public UnitStateComponent {

public:
	ServerUnitStateComponent(Entity* entity);
	virtual ~ServerUnitStateComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual const Position & getPosition();

protected:
};

#endif
