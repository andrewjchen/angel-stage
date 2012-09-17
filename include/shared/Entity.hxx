##ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <map>
#include <stdint.h>

#include "Event.hxx"
#include "Component.hxx"

typedef uint32_t EntityID;

class Entity {
private:
	EntityID _id;
	std::map<ComponentType, Component *> _components;
public:
	EntityID Entity(EntityID id) : _id(id) {};
	virtual ~Entity() {};
	virtual EntityID get_id() const;
	virtual void load_component(ComponentType component_type,
								Component * Component);
	virtual void react(Event * event);
};

#endif /* _ENTITY_HXX_ */
