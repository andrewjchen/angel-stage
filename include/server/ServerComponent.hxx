#ifndef _SERVER_COMPONENT_HXX_
#define _SERVER_COMPONENT_HXX_

#include <stdint.h>

class ServerEntity;

class ServerComponent {
public:
    ServerComponent(ServerEntity *entity) : _entity(entity) {};
    virtual ~ServerComponent() {};
    virtual void tick(double time, double deltaTime) = 0;

protected:
    ServerEntity *_entity;
};

#endif /* _SERVER_COMPONENT_HXX_ */
