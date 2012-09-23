#ifndef _CLIENT_COMPONENT_HXX_
#define _CLIENT_COMPONENT_HXX_

#include <stdint.h>

class ClientEntity;

class ClientComponent {
public:
	ClientComponent(ClientEntity* entity) : _entity(entity) {};
	virtual ~ClientComponent() {};
	virtual void tick(double time, double deltaTime) = 0;

protected:
	ClientEntity * _entity;
};

#endif /* _CLIENT_COMPONENT_HXX_ */
