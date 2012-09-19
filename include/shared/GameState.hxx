#ifndef _GAMESTATE_HXX_
#define _GAMESTATE_HXX_

#include <map>
#include <vector>

#include "Entity.hxx"
#include "Component.hxx"

struct Event;

class GameState {
public:
	GameState(void) {};
	virtual ~GameState(void) {};
	virtual Entity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, Entity * entity);
	virtual void react(Event * event);
	virtual void tick(double time, double deltaTime);

	virtual void addClockListener(Component* toListen);
	virtual void removeClockListener(Component* toListen);

private:
	std::map<EntityID, Entity *> _entities;
	std::vector<Component* > clockReceivers;
};

#endif /* _GAMESTATE_HXX_ */
