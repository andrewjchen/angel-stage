#ifndef _EVENT_TYPES_HXX_
#define _EVENT_TYPES_HXX_

#include "Event.hxx"
#include "Ids.hxx"

const EventTypeID EVENT_GLOBAL_MINIMUM    = 0x81000001;
const EventTypeID EVENT_TEST              = 0x81000001;
const EventTypeID EVENT_DEBUG_MSG         = 0x81000002;
const EventTypeID EVENT_JOIN              = 0x81000003;
const EventTypeID EVENT_UNJOIN            = 0x81000003;
const EventTypeID EVENT_GLOBAL_MAXIMUM    = 0x81010000;

const EventTypeID EVENT_ENTITY_MINIMUM    = 0x81010001;
const EventTypeID EVENT_UNIT_MOVE         = 0x81010002;
const EventTypeID EVENT_UNIT_SPLIT        = 0x81010003;
const EventTypeID EVENT_UNIT_CONSUME      = 0x81010004;
const EventTypeID EVENT_UNIT_ATTACK       = 0x81010005;
const EventTypeID EVENT_UNIT_MERGE        = 0x81010006;
const EventTypeID EVENT_UNIT_FEEDBACK     = 0x81010007;
const EventTypeID EVENT_RESOURCE_FEEDBACK = 0x81010008;
const EventTypeID EVENT_PLAYER_FEEDBACK   = 0x81010009;
const EventTypeID EVENT_ENTITY_MAXIMUM    = 0x81020000;

struct UnitFeedbackEvent {
	EntityEvent header;
	double x;
	double y;
	double theta;
};


#endif /* _EVENT_TYPES_HXX_ */
