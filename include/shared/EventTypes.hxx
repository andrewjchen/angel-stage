##ifndef _EVENT_TYPES_HXX_
#define _EVENT_TYPES_HXX_

#include "Event.hxx"

const EventTypeID EVENT_GLOBAL_MINIMUM   = 0x81 00 00 01;
const EventTypeID EVENT_TEST      = 0x81 00 00 01;
const EventTypeID EVENT_DEBUG_MSG = 0x81 00 00 02;
const EventTypeID EVENT_GLOBAL_MAXIMUM   = 0x81 01 00 00;
const EventTypeID EVENT_ENTITY_MINIMUM   = 0x81 01 00 01;
const EventTypeID EVENT_ENTITY_MAXIMUM   = 0x81 02 00 00;

#endif /* _EVENT_TYPES_HXX_ */
