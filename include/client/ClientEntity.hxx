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

	VisualComponent* _visual_component;
	ClientUnitStateComponent* _unit_state_component;


public:
	ClientEntity(EntityID id) : Entity(id) {};
	~ClientEntity();
	EntityID get_id() const;
	virtual void react(EntityEvent * event);

	ClientGameState* get_gamestate() { return gamestate;};
	void set_gamestate(ClientGameState* gs) { gamestate = gs;};


	VisualComponent* get_visual_component(){ return _visual_component; };
	void set_visual_component(VisualComponent* comp) {_visual_component = comp; };

	ClientUnitStateComponent* get_unit_state_component(){ return _unit_state_component; };
	void set_unit_state_component(ClientUnitStateComponent* comp) { _unit_state_component = comp; };

	
};

#endif /* _ENTITY_HXX_ */
