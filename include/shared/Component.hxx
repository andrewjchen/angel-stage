##ifndef _COMPONENT_HXX_
#define _COMPONENT_HXX_

class Entity;

typedef uint32_t ComponentType;

class Component {
private:
	Entity * _entity;
public:
	Component(Entity * entity) : _entity(entity) {};
	virtual ~Component() {};
};

#endif /* _COMPONENT_HXX_ */
