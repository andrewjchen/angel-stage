#include <cstdio>
#include "ServerGameState.hxx"
#include "Event.hxx"
#include "Debug.hxx"

ServerEntity * ServerGameState::get_entity(EntityID id) {
	if (_entities.count(id) == 0) { //entity doens't exist
		ServerEntity* ent = new ServerEntity(id);
		ent->set_gamestate(this);
		ent->set_unit_state_component(new ServerUnitStateComponent(ent));

		_entities[id] = ent;

	} 
		 
	return _entities[id];
}

void ServerGameState::set_entity(EntityID id, ServerEntity * entity) {
	_entities[id] = entity;
}

void ServerGameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		ServerEntity * e = get_entity(id);
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

void ServerGameState::tick(double wallTime, double deltaTime){
	std::vector<ServerComponent*>::iterator it;
	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void ServerGameState::addClockListener(ServerComponent* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void ServerGameState::removeClockListener(ServerComponent* toListen){
	//TODO test
//	clockReceivers.erase(
//		s td::remove(clockReceivers.begin(), clockReceivers.end(), toListen), clockReceivers.end() );
	std::vector<ServerComponent*>::iterator it;

	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if( (*it) == toListen){
			clockReceivers.erase(it);
		}
	}


}	
