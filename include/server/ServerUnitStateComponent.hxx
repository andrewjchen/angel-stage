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
	virtual void setPosition(Position newpos);

protected:
	Position _pos;
	Position _orbit_pos;
	double _theta;
};

#endif
