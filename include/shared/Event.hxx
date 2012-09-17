#ifndef _EVENT_HXX_
#define _EVENT_HXX_

#include <stdint.h>

typedef uint32_t EventTypeID;

struct Event {
	EventTypeID event_type;
	uint32_t total_byte_count; 
	/* Followed by a dynamically sized package. */
};

typedef struct Event Event;

struct EntityEvent {
    Event header;
	EntityID entity_id;
};

typedef struct EntityEvent EntityEvent;



#endif /* _EVENT_HXX_ */
