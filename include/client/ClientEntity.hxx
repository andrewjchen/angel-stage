#ifndef _CLIENT_ENTITY_HXX_
#define _CLIENT_ENTITY_HXX_

#include <stdint.h>
#include <map>

#include "Entity.hxx"
#include "Ids.hxx"

#include "Event.hxx"
#include "EventTypes.hxx"

class ClientGameState;

class ClientEntity: public Entity {

public:
	ClientEntity(EntityID id, ClientGameState* gamestate);
	virtual ~ClientEntity();
	virtual void react(EntityEvent * event) = 0;
	virtual void tick(double wallTime, double deltaT) = 0;
	//tick

	ClientGameState* get_gamestate();

protected:
	ClientGameState* _gamestate;

};

#endif /* _ENTITY_HXX_ */
