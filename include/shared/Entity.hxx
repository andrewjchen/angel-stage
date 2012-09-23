#ifndef _ENTITY_HXX_
#define _ENTITY_HXX_

#include <stdint.h>
#include <map>
#include "Ids.hxx"

#define DECLARE_COMPONENT(_comp_type_, _comp_name_)					\
	private: _comp_type_ * _##_comp_name_;								\
	public: virtual _comp_type_ * get_##_comp_name_() {				\
		return _##_comp_name_;											\
	};																	\
	public: virtual void set_##_comp_name_(_comp_type_ * _comp_name_) { \
		_##_comp_name_ = _comp_name_;									\
	};

#include "Event.hxx"
#include "EventTypes.hxx"

class Entity {
protected:
	EntityID _id;
public:
	Entity(EntityID id) : _id(id) {};
	virtual ~Entity() {};
	EntityID get_id() const;
	virtual void react(EntityEvent * event);
};

#endif /* _ENTITY_HXX_ */
