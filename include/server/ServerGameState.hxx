#ifndef _SERVER_GAMESTATE_HXX_
#define _SERVER_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ServerEntity.hxx"
#include "ServerComponent.hxx"

struct ServerEvent;
class Server;

class ServerGameState {
public:
	ServerGameState(Server* server);
	virtual ~ServerGameState(void);
	virtual ServerEntity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, ServerEntity * entity);
	virtual void delete_entity(EntityID id);
	virtual void react(Event * event);
	virtual void tick(double time, double deltaTime);
	virtual Server* get_server() { return _server; };
	virtual EntityID spawn_entity();
	virtual EntityID spawn_unit();

	virtual void addClockListener(ServerComponent* toListen);
	virtual void removeClockListener(ServerComponent* toListen);

protected:
	EntityID _next_id;
	std::map<EntityID, ServerEntity *> _entities;
	std::vector<ServerComponent* > clockReceivers;

	Server* _server;
};

#endif /* _GAMESTATE_HXX_ */
