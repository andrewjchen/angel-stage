#ifndef _COMPONENT_HXX_
#define _COMPONENT_HXX_
#include <stdint.h>

#include <stdint.h>

class Entity;

class Component {
public:
	Component(Entity* entity) : _entity(entity) {};
	virtual ~Component() {};

	virtual void tick(double time, double deltaTime) = 0;

protected:
	Entity * _entity;
};

#endif /* _COMPONENT_HXX_ */
