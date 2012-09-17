#ifndef _COMPONENT_HXX_
#define _COMPONENT_HXX_

class Entity;

typedef uint32_t ComponentType;

class Component {
public:
	Component(Entity * entity) : _entity(entity) {};
	virtual ~Component() {};
	
protected:
	Entity * _entity;
};

#endif /* _COMPONENT_HXX_ */
