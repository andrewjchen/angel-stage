#ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <stdint.h>
#include <map>
#include "Ids.hxx"

#include "Event.hxx"
#include "EventTypes.hxx"

class Entity {
protected:
	EntityID _id;
public:
	Entity(EntityID id) : _id(id) {};
	virtual ~Entity() {};
	EntityID get_id() const { return _id; };
	virtual void react(EntityEvent * event);
};

#endif /* _ENTITY_HXX_ */
