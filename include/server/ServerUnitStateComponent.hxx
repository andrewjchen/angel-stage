#ifndef _SERVER_UNIT_STATE_COMPONENT_HXX_
#define _SERVER_UNIT_STATE_COMPONENT_HXX_

#include "Position.hxx"
#include "ServerComponent.hxx"

class ServerUnitStateComponent : public ServerComponent {

public:
	ServerUnitStateComponent(ServerEntity* entity);
	virtual ~ServerUnitStateComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual const Position & getPosition();

protected:
	Position _pos;
	double _theta;
};

#endif
