#include <cstdio>
#include "ClientEntity.hxx"
#include "EventTypes.hxx"

void ClientEntity::react(EntityEvent * event) {
	printf("Entity at %p received event!\n", this);
	switch (event->header.event_type) {
		case (EVENT_UNIT_FEEDBACK):
			if (_unit_state_component) {
				_unit_state_component->feedback((UnitFeedbackEvent *) event);
			}
			break;
	}
}
