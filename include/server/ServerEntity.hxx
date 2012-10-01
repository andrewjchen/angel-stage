#ifndef _SERVER_ENTITY_HXX_
#define _SERVER_ENTITY_HXX_

#include <stdint.h>
#include <map>

#include "Entity.hxx"
#include "Ids.hxx"
#include "ServerComponent.hxx"

#include "Event.hxx"
#include "EventTypes.hxx"

class ServerGameState;

class ServerEntity : public Entity {
public:
	ServerEntity(EntityID id, ServerGameState * gamestate);
	virtual ~ServerEntity();
	virtual void react(EntityEvent * event) = 0;
	virtual void tick(double wallTime, double deltaT) = 0;

	ServerGameState* get_gamestate();
	//void set_gamestate(ServerGameState* state);

protected:
	//EntityID _id;
	ServerGameState* _gamestate;

};

#endif /* _ENTITY_HXX_ */
