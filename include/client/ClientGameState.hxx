#ifndef _Client_GAMESTATE_HXX_
#define _Client_GAMESTATE_HXX_

#include <map>
#include <vector>

#include "ClientEntity.hxx"
#include "ClientComponent.hxx"
#include "Renderer.hxx"

struct ClientEvent;

class ClientGameState {
public:
	ClientGameState(Renderer *render)
	{
		globalRenderer = render;
	};
	virtual ~ClientGameState(void) {};
	virtual ClientEntity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, ClientEntity * entity);
	virtual void react(Event * event);
	virtual void tick(double time, double deltaTime);

	virtual void addClockListener(ClientComponent* toListen);
	virtual void removeClockListener(ClientComponent* toListen);
	
	Renderer *globalRenderer;

private:
	std::map<EntityID, ClientEntity *> _entities;
	std::vector<ClientComponent* > clockReceivers;
};

#endif /* _GAMESTATE_HXX_ */
