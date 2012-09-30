#ifndef _SERVER_UNIT_POSE_COMPONENT_HXX_
#define _SERVER_UNIT_POSE_COMPONENT_HXX_


#include "Ids.hxx"
#include "Position.hxx"
#include "Ids.hxx"
#include "ServerComponent.hxx"

/**
 * Pose is position and orientation
 */
class Pose: public ServerComponent {

public:
	Pose(ServerEntity* entity);
	virtual ~Pose();
	virtual void tick(double wallTime, double deltaT);
	const Position & get_position();
	void set_position(Position pos);
	
	virtual double get_orientation();
	void set_orientation(double orientation);
	//virtual void sync();

protected:
	Position _pos;
	double _theta;
};

#endif
