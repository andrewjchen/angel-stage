#ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <stdint.h>
#include <map>

#include "Ids.hxx"
#include "Component.hxx"
#include "UnitStateComponent.hxx"

#ifdef CLIENT_SIDE
#include "VisualComponent.hxx"
#include "ClientUnitStateComponent.hxx"
#endif

#ifdef SERVER_SIDE
#include "ServerUnitStateComponent.hxx"
#endif

#define DECLARE_COMPONENT(_comp_type_, _comp_name_)					\
	private: _comp_type_ * _##_comp_name_;								\
	public: virtual _comp_type_ * get_##_comp_name_() {				\
		return _##_comp_name_;											\
	};																	\
	public: virtual void set_##_comp_name_(_comp_type_ * _comp_name_) { \
		_##_comp_name_ = _comp_name_;									\
	};

class GameState;

#include "Event.hxx"
#include "EventTypes.hxx"

class Entity {
protected:
	EntityID _id;
	GameState * gamestate;
public:
	Entity(EntityID id) : _id(id) {};
	~Entity() {};
	EntityID get_id() const;
	void react(EntityEvent * event);
	GameState* get_gamestate();
	void set_gamestate(GameState* gs) { gamestate = gs;};
#ifdef CLIENT_SIDE
	DECLARE_COMPONENT(VisualComponent, visual_component);
	DECLARE_COMPONENT(ClientUnitStateComponent, unit_state_component);
#endif
#ifdef SERVER_SIDE
	DECLARE_COMPONENT(ServerUnitStateComponent, unit_state_component);

#endif
};

#endif /* _ENTITY_HXX_ */
