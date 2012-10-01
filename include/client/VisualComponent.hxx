#ifndef _VISUAL_COMPONENT_HXX_
#define _VISUAL_COMPONENT_HXX_

#include "ClientComponent.hxx"
#include "EventTypes.hxx"
#include "Position.hxx"

struct Client;

class VisualComponent : public ClientComponent {

public:
	VisualComponent(ClientEntity* entity);
	virtual ~VisualComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual void render(const Position & viewpoint, Client * client);
};

#endif /* _VISUAL_COMPONENT_HXX_ */
