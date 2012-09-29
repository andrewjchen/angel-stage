#ifndef _SERVER_ENTITY_HXX_
#define _SERVER_ENTITY_HXX_

#include <stdint.h>
#include <map>

#include "Entity.hxx"
#include "Ids.hxx"
#include "ServerComponent.hxx"

#include "ServerUnitStateComponent.hxx"

#include "Event.hxx"
#include "EventTypes.hxx"

class ServerGameState;

class ServerEntity : public Entity {
protected:
	ServerGameState* gamestate;

	ServerUnitStateComponent* _unit_state_component;

public:
	ServerEntity(EntityID id) : Entity(id) {};
	virtual ~ServerEntity() {};
	virtual void react(EntityEvent * event);

	ServerGameState* get_gamestate() { return gamestate; };
	void set_gamestate(ServerGameState* state) { gamestate = state; };

	//DECLARE_COMPONENT(ServerUnitStateComponent, unit_state_component);

	ServerUnitStateComponent* get_unit_state_component(){ return _unit_state_component; };
	void set_unit_state_component(ServerUnitStateComponent* comp) {_unit_state_component = comp; };

};

#endif /* _ENTITY_HXX_ */
