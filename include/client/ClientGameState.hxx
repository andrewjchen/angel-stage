s#ifndef _Client_GAMESTATE_HXX_
#define _Client_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ClientEntity.hxx"
#include "Renderer.hxx"

class ClientEvent;
struct Client;

class ClientGameState {
public:
    ClientGameState(Client *client) {
        _client = client;
    };
    virtual ~ClientGameState(void);
    virtual ClientEntity *get_entity(EntityID id);
    virtual void set_entity(EntityID id, ClientEntity *entity);
    virtual void delete_entity(EntityID id);
    virtual bool entity_exists(EntityID);
    virtual void react(Event *event);
    virtual void tick(double time, double deltaTime);

    virtual void add_clock_listener(ClientEntity *toListen);
    virtual void remove_clock_listener(ClientEntity *toListen);
    virtual std::vector<ClientEntity *> * get_entities_in_rect(const Position &p1, const Position &p2);

    Renderer *globalRenderer;


private:
    std::map<EntityID, ClientEntity *> _entities;
    std::vector<ClientEntity * > clockReceivers;

    Client *_client;
};

#endif /* _GAMESTATE_HXX_ */
