##ifndef _GAMESTATE_HXX_
#define _GAMESTATE_HXX_

#include <map>

#include "Entity.hxx"

class GameState{
private:
	std::map<EntityID, Entity *> _entities;
public:
	GameState(void) {};
	virtual ~GameState(void) {};
	virtual Entity * get_entity(EntityID id);
	virtual void react(Event * event);
};

#endif /* _GAMESTATE_HXX_ */
