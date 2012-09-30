#ifndef _SERVER_UNIT_HXX_
#define _SERVER_UNIT_HXX_

//superclass
#include "ServerEntity.hxx"
//components
#include "Pose.hxx"
#include "Size.hxx"


/**
 * A Unit has a pose and size.
 */
class Unit: public ServerEntity {

public:
	Unit(
		EntityID id, 
		ServerGameState* gamestate);
	virtual ~Unit();
	virtual void react(EntityEvent * event);

	Pose* get_pose();
	void set_pose(Pose* pose);

	Size* get_size();
	void set_size(Size* size);

private:
	Pose* _pose;
	Size* _size;


	//ServerUnitStateComponent* get_unit_state_component(){ return _unit_state_component; };
	//void set_unit_state_component(ServerUnitStateComponent* comp) {_unit_state_component = comp; };

};

#endif /* _ENTITY_HXX_ */
