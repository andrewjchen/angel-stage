#ifndef _GAMESTATE_HXX_
#define _GAMESTATE_HXX_

#include <map>

#include "Entity.hxx"

struct Event;

class GameState {
private:
	std::map<EntityID, Entity *> _entities;
public:
	GameState(void) {};
	virtual ~GameState(void) {};
	virtual Entity * get_entity(EntityID id);
	virtual void set_entity(EntityID id, Entity * entity);
	virtual void react(Event * event);
};

#endif /* _GAMESTATE_HXX_ */
