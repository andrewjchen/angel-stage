#ifndef _SERVER_UNIT_STATE_COMPONENT_HXX_
#define _SERVER_UNIT_STATE_COMPONENT_HXX_

#include "Position.hxx"
#include "ServerComponent.hxx"

const double UNIT_VELOCITY = 100.0;

class ServerUnitStateComponent : public ServerComponent {

public:
	ServerUnitStateComponent(ServerEntity* entity);
	virtual ~ServerUnitStateComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual const Position & getPosition();
	virtual void setPosition(Position newpos);

	virtual void setGoal(Position goal);

protected:
	Position _pos;
	Position _orbit_pos;

	double _xVel;
	double _yVel;

	Position _goal;
	double _theta;
};

#endif
