#include <cstdio>
#include "GameState.hxx"
#include "EventTypes.hxx"

#include "Debug.hxx"
Entity * GameState::get_entity(EntityID id) {
	if (_entities.count(id)) {
		return _entities[id];
	} else {
		return NULL;
	}
}

void GameState::set_entity(EntityID id, Entity * entity) {
	_entities[id] = entity;
}

void GameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		Entity * e = get_entity(id);
		if (e) {
			e->react((EntityEvent *) event);
		}
	} else if (is_global_event(event)) {
		/* TODO: Do things. */
		printf("Received global event!\n");
		switch (event->event_type) {
		case EVENT_TEST:
			printf("Received a test event!\n");
			break;
		}
	}
}

void GameState::tick(double wallTime, double deltaTime){
	std::vector<Component*>::iterator it;
	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void GameState::addClockListener(Component* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void GameState::removeClockListener(Component* toListen){
	//TODO test
//	clockReceivers.erase(
//		s td::remove(clockReceivers.begin(), clockReceivers.end(), toListen), clockReceivers.end() );
	std::vector<Component*>::iterator it;

	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if( (*it) == toListen){
			clockReceivers.erase(it);
		}
	}


}	
