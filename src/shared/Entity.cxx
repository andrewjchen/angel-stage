#include <cstdio>
#include "Entity.hxx"
#include "EventTypes.hxx"

EntityID Entity::get_id() const {
	return _id;
}
GameState* Entity::get_gamestate(){
	return gamestate;
}

void Entity::react(Event * event) {
	printf("Entity at %p received event!\n", this);
	// switch (event->header.event_type) {
	// case (EVENT_UNIT_FEEDBACK):
	// 	if (_state_component) {
	// 		_state_component->update((UnitFeedbackEvent *) event);
	// 	}
	// }
	/* TODO: Do things. */
}

