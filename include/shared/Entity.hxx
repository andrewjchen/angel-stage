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
    Entity(EntityID id);
    virtual ~Entity();
    EntityID get_id();
    virtual void react(EntityEvent *event) = 0;
};

#endif /* _ENTITY_HXX_ */
