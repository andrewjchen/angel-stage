#include "Event.hxx"
#include "EventTypes.hxx"

bool is_global_event(Event * event) {
	EventTypeID id = event->event_type;
	if (EVENT_GLOBAL_MINIMUM <= id && id <= EVENT_GLOBAL_MAXIMUM) {
		return true;
	} else {
		return false;
	}
}

bool is_entity_event(Event * event) {
	EventTypeID id = event->event_type;
	if (EVENT_ENTITY_MINIMUM <= id && id <= EVENT_ENTITY_MAXIMUM) {
		return true;
	} else {
		return false;
	}
}
