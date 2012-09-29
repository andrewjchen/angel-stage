#include <cstdio>
#include "ClientEntity.hxx"
#include "EventTypes.hxx"
#include "Debug.hxx"

void ClientEntity::react(EntityEvent * event) {
	//printf("Entity at %p received event!\n", this);
	switch (event->header.event_type) {
		case (EVENT_UNIT_FEEDBACK):
		case (EVENT_UNIT_MOVE):
			if (_unit_state_component) {
				UnitFeedbackEvent *ufe = (UnitFeedbackEvent*)(event);
				//DEBUG("Move entity with id=" << ufe->header.entity_id << ", x=" <<ufe->x << ", y=" << ufe->y);
				_unit_state_component->feedback(ufe);
			}
			break;
	}
}

ClientEntity::~ClientEntity() {
	delete _visual_component;
	delete _unit_state_component;
}
