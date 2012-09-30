#ifndef _Client_GAMESTATE_HXX_
#define _Client_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ClientEntity.hxx"
#include "ClientComponent.hxx"
#include "Renderer.hxx"

struct ClientEvent;
class Client;

class ClientGameState {
public:
	ClientGameState(Client* client, Renderer *render)
	{
		_client = client;
		globalRenderer = render;
	};
	virtual ~ClientGameState(void);
	virtual ClientEntity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, ClientEntity * entity);
	virtual void delete_entity(EntityID id);
	virtual void react(Event * event);
	virtual void tick(double time, double deltaTime);

	virtual void addClockListener(ClientComponent* toListen);
	virtual void removeClockListener(ClientComponent* toListen);
	virtual std::vector<ClientEntity *> * get_entities_in_rect(const Position & p1, const Position & p2);

	Renderer *globalRenderer;


private:
	std::map<EntityID, ClientEntity *> _entities;
	std::vector<ClientComponent* > clockReceivers;

	Client* _client;
};

#endif /* _GAMESTATE_HXX_ */
