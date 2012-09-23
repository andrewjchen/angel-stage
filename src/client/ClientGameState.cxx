#include <cstdio>
#include "ClientGameState.hxx"
#include "Event.hxx"
#include "Debug.hxx"

ClientEntity * ClientGameState::get_entity(EntityID id) {
	if (_entities.count(id)) {
		return _entities[id];
	} else {
		return NULL;
	}
}

void ClientGameState::set_entity(EntityID id, ClientEntity * entity) {
	_entities[id] = entity;
}

void ClientGameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		ClientEntity * e = get_entity(id);
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

void ClientGameState::tick(double wallTime, double deltaTime){
	std::vector<ClientComponent*>::iterator it;
	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void ClientGameState::addClockListener(ClientComponent* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void ClientGameState::removeClockListener(ClientComponent* toListen){
	//TODO test
//	clockReceivers.erase(
//		s td::remove(clockReceivers.begin(), clockReceivers.end(), toListen), clockReceivers.end() );
	std::vector<ClientComponent*>::iterator it;

	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if( (*it) == toListen){
			clockReceivers.erase(it);
		}
	}


}	
