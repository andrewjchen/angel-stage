#ifndef _SERVER_GAMESTATE_HXX_
#define _SERVER_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ServerEntity.hxx"
#include "ServerComponent.hxx"

struct ServerEvent;

class ServerGameState {
public:
	ServerGameState(void) {};
	virtual ~ServerGameState(void) {};
	virtual ServerEntity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, ServerEntity * entity);
	virtual void react(Event * event);
	virtual void tick(double time, double deltaTime);

	virtual void addClockListener(ServerComponent* toListen);
	virtual void removeClockListener(ServerComponent* toListen);

private:
	std::map<EntityID, ServerEntity *> _entities;
	std::vector<ServerComponent* > clockReceivers;
};

#endif /* _GAMESTATE_HXX_ */
