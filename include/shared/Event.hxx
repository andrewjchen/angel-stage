#ifndef _EVENT_HXX_
#define _EVENT_HXX_

#include "Ids.hxx"
#include <stdint.h>


struct Event {
	EventTypeID event_type;
	uint32_t total_byte_count; 
	/* Followed by a dynamically sized package. */
};

struct EntityEvent {
    Event header;
	EntityID entity_id;
};

bool is_global_event(Event * event);
bool is_entity_event(Event * event);

#endif /* _EVENT_HXX_ */
