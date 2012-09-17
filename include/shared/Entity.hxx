#ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <map>
#include <stdint.h>

#include "Event.hxx"
#include "Component.hxx"

#define DECLARE_COMPONENT(_comp_type_, _comp_name_)					\
	private _comp_type_ * _##_comp_name_;								\
	virtual public _comp_type_ * get_##_comp_name_() {					\
		return _##_comp_name_;											\
	};																	\
	virtual public void set_##_comp_name_(_comp_type_ * _comp_name_) {	\
		_##_comp_name_ = _comp_name_;									\
	};

class GameState;

typedef uint32_t EntityID;

class Entity {
private:
	EntityID _id;
	GameState * gamestate;
public:
	EntityID Entity(EntityID id) : _id(id) {};
	virtual ~Entity() {};
	virtual EntityID get_id() const;
	virtual void react(Event * event);
	DECLARE_COMPONENT(StateComponent, state_component)
#ifdef CLIENT_SIDE
	DECLARE_COMPONENT(VisualComponent, visual_component)
#endif
#ifdef SERVER_SIDE
	DECLARE_COMPONENT(VisualComponent, visual_component)
#endif
};

#endif /* _ENTITY_HXX_ */
