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
	EntityID _id;
	ServerGameState* _gamestate;
	ServerUnitStateComponent* _unit_state_component;

public:
	ServerEntity(EntityID id, ServerGameState * gamestate) : Entity(id),
															 _gamestate(gamestate) {};
	virtual ~ServerEntity();
	virtual void react(EntityEvent * event);

	ServerGameState* get_gamestate() { return _gamestate; };
	void set_gamestate(ServerGameState* state) { _gamestate = state; };

	ServerUnitStateComponent* get_unit_state_component(){ return _unit_state_component; };
	void set_unit_state_component(ServerUnitStateComponent* comp) {_unit_state_component = comp; };

};

#endif /* _ENTITY_HXX_ */
