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
public:
	ServerEntity(EntityID id) : Entity(id) {};
	virtual ~ServerEntity() {};

	ServerGameState* get_gamestate() { return gamestate; };
	void set_gamestate(ServerGameState* state) { gamestate = state; };

	DECLARE_COMPONENT(ServerUnitStateComponent, unit_state_component);

};

#endif /* _ENTITY_HXX_ */
