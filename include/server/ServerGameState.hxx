#ifndef _SERVER_GAMESTATE_HXX_
#define _SERVER_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ServerEntity.hxx"

struct ServerEvent;
class Server;

class ServerGameState {
public:
    ServerGameState(Server *server);
    virtual ~ServerGameState(void);
    virtual ServerEntity *get_entity(EntityID id);
    virtual void set_entity(EntityID id, ServerEntity *entity);
    virtual void delete_entity(EntityID id);
    virtual void react(Event *event);
    virtual void tick(double time, double deltaTime);
    virtual Server *get_server() {
        return _server;
    };
    virtual EntityID spawn_unit();

    virtual void add_clock_listener(ServerEntity *toListen);
    virtual void remove_clock_listener(ServerEntity *toListen);

protected:
    EntityID _next_id;
    std::map<EntityID, ServerEntity *> _entities;
    std::vector<ServerEntity * > clockReceivers;

    Server *_server;
};

#endif /* _GAMESTATE_HXX_ */
