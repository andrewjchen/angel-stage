#include <cstdio>
#include "Entity.hxx"
#include "EventTypes.hxx"

EntityID Entity::get_id() const {
	return _id;
}

GameState* Entity::get_gamestate(){
	return gamestate;
}

void Entity::react(EntityEvent * event) {
	printf("Entity at %p received event!\n", this);
	switch (event->header.event_type) {
	case (EVENT_UNIT_FEEDBACK):
		if (_unit_state_component) {
			_unit_state_component->feedback((UnitFeedbackEvent *) event);
		}
		break;
	}
}
