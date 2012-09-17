#include "GameState.hxx"
#include "Event.hxx"

virtual Entity * GameState::get_entity(EntityID id) {
	if (_entities.count(id)) {
		return _entities[id];
	} else {
		return NULL;
	}
}

virtual void GameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		Entity * e = get_entity(id);
		if (e) {
			e.react(event);
		}
	} else if (is_global_event(event)) {
		/* TODO: Do things. */
		printf("Received global event!");
		switch (event->event_type) {
		case EVENT_TEST:
			printf("Received a test event!\n");
			break;
		}
	}
}
