#include <cstdio>
#include "Entity.hxx"
#include "EventTypes.hxx"

void Entity::react(EntityEvent * event) {
	printf("Entity at %p received event!\n", this);
	switch (event->header.event_type) {
		#ifdef CLIENT_SIDE
		case (EVENT_UNIT_FEEDBACK):
			if (_unit_state_component) {
				_unit_state_component->feedback((UnitFeedbackEvent *) event);
			}
			break;
		#endif
	}
}
