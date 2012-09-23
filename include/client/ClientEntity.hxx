#ifndef _CLIENT_ENTITY_HXX_
#define _CLIENT_ENTITY_HXX_

#include <stdint.h>
#include <map>

#include "Entity.hxx"
#include "Ids.hxx"
#include "ClientComponent.hxx"

#include "VisualComponent.hxx"
#include "ClientUnitStateComponent.hxx"

#include "Event.hxx"
#include "EventTypes.hxx"

class ClientGameState;

class ClientEntity: public Entity {
protected:
	ClientGameState* gamestate;
public:
	ClientEntity(EntityID id) : Entity(id) {};
	~ClientEntity();
	EntityID get_id() const;
	virtual void react(EntityEvent * event);
	ClientGameState* get_gamestate() { return gamestate;};
	void set_gamestate(ClientGameState* gs) { gamestate = gs;};

	DECLARE_COMPONENT(VisualComponent, visual_component);
	DECLARE_COMPONENT(ClientUnitStateComponent, unit_state_component);
};

#endif /* _ENTITY_HXX_ */
