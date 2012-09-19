#ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <map>
#include <stdint.h>

#include "Component.hxx"
#include "UnitStateComponent.hxx"

#define DECLARE_COMPONENT(_comp_type_, _comp_name_)					\
	private: _comp_type_ * _##_comp_name_;								\
	public: virtual _comp_type_ * get_##_comp_name_() {				\
		return _##_comp_name_;											\
	};																	\
	public: virtual void set_##_comp_name_(_comp_type_ * _comp_name_) { \
		_##_comp_name_ = _comp_name_;									\
	};

class GameState;

typedef uint32_t EntityID;

// #include "Event.hxx"

struct EntityEvent;

class Entity {
private:
	EntityID _id;
	GameState * gamestate;
public:
	Entity(EntityID id) : _id(id) {};
	~Entity() {};
	EntityID get_id() const;
	void react(Event * event);
	GameState* get_gamestate();
	void set_gamestate(GameState* gs) { gamestate = gs;};
	DECLARE_COMPONENT(UnitStateComponent, unit_state_component);
#ifdef CLIENT_SIDE
	DECLARE_COMPONENT(VisualComponent, visual_component);
#endif
#ifdef SERVER_SIDE
	DECLARE_COMPONENT(VisualComponent, visual_component);
#endif
};

#endif /* _ENTITY_HXX_ */
